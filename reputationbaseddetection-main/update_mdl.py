ips = {}
with open("mdl.csv", 'r', encoding='utf-16') as mdl:
    for line in mdl:
        info = line.replace('"', '').strip()
        info = info.split(',')
        if len(info) == 10:
            if '/' in info[2]:
                info[2] = info[2].split("/")[0]
            if ':' in info[2]:
                info[2] = info[2].split(':')[0]
            if info[2] not in ips:
                ips[info[2]] = {"score": 1}
            else:
                if ips[info[2]]["score"] < 127:
                    ips[info[2]]["score"] += 1

with open("ip.txt", 'r') as mdl:
    for line in mdl:
        line = line.strip()
        if line not in ips:
            ips[line] = {"score": 1}
        else:
            if ips[line]["score"] < 127:
                ips[line]["score"] += 1

with open("mdl.list", 'w') as mdl:
    for ip, info in ips.items():
        mdl.write(f"{ip},1,{info['score']}\n")
