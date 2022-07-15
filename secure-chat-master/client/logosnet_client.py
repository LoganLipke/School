import argparse
import socket
import select
import queue
import sys
import LNP
from cryptography.fernet import Fernet

def get_args():
    '''
    Gets command line argumnets.
    '''

    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--port",
        metavar='p',
        dest='port',
        help="port number",
        type=int,
        default=42069
    )

    parser.add_argument(
        "--ip",
        metavar='i',
        dest='ip',
        help="IP address for client",
        default='127.0.0.1'
    )

    return parser.parse_args()

def create_key():
    return Fernet.generate_key().decode()

def encrypt_msg(msg, key):
    '''
    returns msg encrypted with key
    '''
    f = Fernet(key.encode())
    return f.encrypt(msg.encode()).decode()

def decrypt_msg(msg, key):
    '''
    returns msg decrypted with key
    '''
    f = Fernet(key.encode())
    return f.decrypt(msg.encode()).decode()

#Main method
def main():
    '''
    uses a select loop to process user and server messages. Forwards user input to the server.
    '''

    args = get_args()
    server_addr = args.ip
    port = args.port

    server = socket.socket()
    server.connect((server_addr, port))

    msg_buffer = {}
    recv_len = {}
    msg_len = {}
    msg_ids = {}
    symmetric_keys = {}
    pvt_msg_hold = [False, '']

    inputs = [server, sys.stdin]
    outputs = [server]
    message_queue = queue.Queue()

    waiting_accept = True
    username = ''
    username_next = False

    dh_wait = False

    while server in inputs:

        readable, writable, exceptional = select.select(inputs, outputs, inputs)

        for s in readable:

            ###
            ### Process server messages
            ###
            if s == server:
                
                # This point may iterate multiple times until the message is completely read since LNP.recv, receives a few bytes at a time.
                code = LNP.recv(s, msg_buffer, recv_len, msg_len, msg_ids)
                # This will not happen until the message is switched to MSG_COMPLETE when then it is read from the buffer.
                if code != "LOADING_MSG":
                    code_id, msg = LNP.get_msg_from_queue(s, msg_buffer, recv_len, msg_len, msg_ids, symmetric_keys)
                    
                    if code_id is not None:
                        code = code_id
                        # print("Message ID: " + id)

                    #print(f"DEBUG======= {msg} {code}")
                if code == "MSG_CMPLT":
                    
                    if username_next:
                        print("complete")
                        username_msg = msg
                        username = username_msg.split(' ')[1]
                        sys.stdout.write(username_msg + '\n')
                        sys.stdout.write("> " + username + ": ")
                        sys.stdout.flush()
                        username_next = False

                    elif msg:
		        #If username exists, add message prompt to end of message
                        if username != '':
                            sys.stdout.write('\r' + msg + '\n')
                            sys.stdout.write("> " + username + ": ")

                        #If username doesnt exist, just write message
                        else:
                            sys.stdout.write(msg)

                        sys.stdout.flush()

                # This and any other codes can be edited in protocol.py, this way you can add new codes for new states, e.g., is this a public key, CODE is PUBKEY and msg contains the key.
                elif code == "ACCEPT":
                    waiting_accept = False
                    sys.stdout.write(msg)
                    sys.stdout.flush()

                elif code == "USERNAME-INVALID" or code == "USERNAME-TAKEN":
                    sys.stdout.write(msg)
                    sys.stdout.flush()

                elif code == "USERNAME-ACCEPT":
                    username_next = True

                elif code == "NO_MSG" or code == "EXIT":
                    sys.stdout.write(msg + '\n')
                    sys.stdout.flush()
                    inputs.remove(s)
                    if s in writable:
                        writable.remove(s)

                elif code == "DH-HELLO":
                    temp = msg.split(" ")
                    pvt_user = temp[1][1:]
                    symmetric_keys[pvt_user] = [create_key(), None]
                    if pvt_msg_hold[0]:
                        LNP.send(s, f"@{pvt_user} |{username} " + symmetric_keys[pvt_user][0], "DH-KEY-EXCHANGE")
                        dh_wait = False
                    else:
                        LNP.send(s, f"@{pvt_user} |{username} ", "DH-HELLO")

                elif code == "DH-KEY-EXCHANGE":
                    temp = msg.split(" ")
                    pvt_user = temp[1][1:]
                    symmetric_keys[pvt_user][1] = temp[2]
                    #print(symmetric_keys)
                    LNP.send(s, f"@{pvt_user} |{username}", "DH-REPLY")

                elif code == "DH-REPLY":
                    if pvt_msg_hold:
                        temp = msg.split(" ")
                        pvt_user = temp[1][1:]
                        pvt_msg_hold[0] = False
                        #print("DEBUG------------", pvt_msg_hold)
                        pvt_msg = encrypt_msg(pvt_msg_hold[1], symmetric_keys[pvt_user][0])

                        LNP.send(s, f"@{pvt_user} |{username} " + pvt_msg, "PVT-MSG")
                        pvt_msg_hold[1] = ''

                elif code == "PVT-MSG":
                    temp = msg.split(" ")
                    pvt_user = temp[1][1:]
                    #print("DEBUG++++++++", temp)
                    msg = decrypt_msg(temp[2], symmetric_keys[pvt_user][1])
                    sys.stdout.write(f"\n> {pvt_user}: {msg}\n")
                    sys.stdout.write("> " + username + ": ")
                    sys.stdout.flush()
            ###
            ### Process user input
            ###
            else:

                msg = sys.stdin.readline()

                if not waiting_accept:
                    msg = msg.rstrip()
                    if msg:
                        message_queue.put(msg)
                    if not ((username == '') or (msg == "exit()")):
                        sys.stdout.write("> " + username + ": ")
                        sys.stdout.flush()

        ###
        ### Send messages to server
        ###
        for s in writable:

            try:
                msg = message_queue.get_nowait()
            except queue.Empty:
                msg = None

	 #if there is a message to send
            if msg:

	     #if exit message, send the exit code
                if msg == "exit()":
                    outputs.remove(s)
                    LNP.send(s, '', "EXIT")

             #if message should be a private message
                elif msg[0] == '@':
                    #check if key already known
                    if msg[1:] in symmetric_keys:
                         msg_pt1 = msg[:msg.index(" ")]
                         msg_pt2 = msg[msg.index(" ") + 1:]
                         msg = msg_pt1 + encrypt_msg(msg_pt2, symmetric_keys[s][0])
                         LNP.send(s, msg, "PVT-MSG")
                    else:
                         pvt_msg_hold = [True, msg]
                         dh_wait = True
                         LNP.send(s, msg[:msg.index(" ")] + " |" + username, "DH-HELLO")

	     #otherwise just send the messsage
                else:
                    if username == '':
                        cert = ""
                        try:
                           cert = "|" + str(open(msg+".cert","rb").read())
                        except FileNotFoundError:
                           print("Valid cert file not found!")
                           exit(1)
                        finally:
                           msg = msg + cert
                    LNP.send(s, msg)

        for s in exceptional:
            print("Disconnected: Server exception")
            inputs.remove(s)

    server.close()

if __name__ == '__main__':
    main()
