import subprocess

def pdreceive(port, tcp=True):
    args = ["pdreceive", str(port), "tcp" if tcp else "udp"]
    proc = subprocess.Popen(args, stdout=subprocess.PIPE)
    while True:
        line = proc.stdout.readline()
        if line == '': # `pdreceive` exited.
            break
        yield line

for message in pdreceive(3000):
    print (message)
