#!/usr/bin/env python3
import re
import argparse

"""
Author: Logan Lipke
CISS 360 Winter 2021
Assignment 1
"""
def parse_file(file="", timestamp="", user="", log_msg="", mode=4, print_results=False):

    with open(file, 'r') as file: 
        lines = file.readlines()

    log_reg= r"(\w+ \d+ \d+:\d+:\d+) (\S+) (.+)"
    reg = re.compile(log_reg)
    count_timestamp = 0
    count_user = 0
    count_log_msg = 0
    for line in lines:
        match = reg.match(line)
        if match:
            match_timestamp = match.group(1)
            match_user = match.group(2)
            match_log_msg = match.group(3)
        
            if  mode == 1 and (timestamp != "" and timestamp in match_timestamp):
                print("\n[+] Timestamp '%s' matched!" % timestamp)
                count_timestamp += 1
                if print_results:
                    print("\tTimestamp:  \t", match_timestamp)
                    print("\tUser:       \t", match_user)
                    print("\tLog Message:\t", match_log_msg)
            
            elif mode == 2 and (user != "" and user in match_user):
                print("\n[+] User '%s' matched!" % user)
                count_user += 1
                if print_results:
                    print("\tTimestamp:  \t", match_timestamp)
                    print("\tUser:       \t", match_user)
                    print("\tLog Message:\t", match_log_msg)

            elif mode == 3 and (log_msg != "" and log_msg in match_log_msg):
                print("\n[+] Log Message '%s' matched!" % log_msg)
                count_log_msg += 1
                if print_results:
                    print("\tTimestamp:  \t", match_timestamp)
                    print("\tUser:       \t", match_user)
                    print("\tLog Message:\t", match_log_msg)
            
            elif mode == 4 and (log_msg != "" and log_msg in match_log_msg) and (user != "" and user in match_user) and (timestamp != "" and timestamp in match_timestamp):
                print("\n[+] All matched")
                count_timestamp += 1
                count_user += 1
                count_log_msg += 1
                if print_results:
                    print("\tTimestamp:  \t", match_timestamp)
                    print("\tUser:       \t", match_user)
                    print("\tLog Message:\t", match_log_msg)
    
    print("\n======Log Info======")
    if mode == 1:
        print("Mode: Match Timestamp : '%s'" % timestamp)
        print("Timestamps Matched: %d" % count_timestamp)
    elif mode == 2:
        print("Mode: Match User : '%s'" % user)
        print("Users Matched: %d" % count_user)
    elif mode == 3:
        print("Mode: Match Log Message : '%s'" % log_msg)
        print("Log Messages Matched: %d" % count_log_msg)
    else:
        print("Mode: Match All: '%s', '%s', '%s'" % (timestamp, user, log_msg))
        print("Timestamps Matched: %d" % count_timestamp)
        print("Users Matched: %d" % count_user)
        print("Log Messages Matched: %d" % count_log_msg)



def main():
    parser = argparse.ArgumentParser(description="Customizable utility for reading log files, uses regex to parse lines for timestamp, user, and log messages. \
    Intended to work with files in format 'Month Day HH:MM:ss User log_msg'")

    parser.add_argument('-f', '--file', help='Set name of log file to parse', default=None)
    parser.add_argument('-m','--mode', help='Set mode for matching. <timestamp, user, log_msg, or all>', default=None)
    parser.add_argument('-t', '--timestamp', help='String to check for in timestamp regex match. Use "" to allow any match', default=None)
    parser.add_argument('-u', '--user', help='String to check for in user regex match. Use "" to allow any match', default=None)
    parser.add_argument('-l', '--log_msg', help='String to check for in log message regex match. Use "" to allow any match', default=None)
    parser.add_argument('-v', '--verbose', help='If set, will print each matched line with strings found in each for specified mode.', action="store_true", default=False)

    args = parser.parse_args()
    if args.mode is not None:
        if args.mode == "timestamp":
            if args.timestamp is not None:
                mode = 1
            else:
                raise ValueError("Timestamp string to search for must be specified!")
                exit(1)
        elif args.mode == "user":
            if args.user is not None:
                mode = 2
            else:
                raise ValueError("User string to search for must be specified!")
                exit(1)
        elif args.mode == "log_msg":
            if args.log_msg is not None:
                mode = 3
            else:
                raise ValueError("Log Message string to search for must be specified!")
                exit(1)
        elif args.mode == "all":
            if args.timestamp is not None and args.user is not None and args.log_msg is not None:
                mode = 4
            else:
                raise ValueError("Timestamp, User, and Log Message string to search for must be specified!")
                exit(1)
    else:
        raise ValueError("Mode must be specified!")
        exit(1)
    
    if args.file is None:
        raise ValueError("Filename must be set!")
        exit(1)
    
    parse_file(file=args.file, timestamp=args.timestamp, user=args.user, log_msg=args.log_msg, mode=mode, print_results=args.verbose)

if __name__ == "__main__":
    main()