import subprocess
import sys

def config(val):
    subprocess.call('cmake -G Ninja -B build/ ' + val.upper(), shell=True)

def build(config = 'Debug', target = 'all'): 
    subprocess.call('cmake --build build/ --config ' + config + ' --target ' + target, shell=True)

def help():
    print('''
          OPTIONS:
                -h          Display help list

                -conf       Configure cmake project
                -build      Build project (Can specify cmake target configuration)
                                ex:
                                    -build Debug
                                    -build Release
                                    -build          (defaults to "Debug")

                -t          Target(s) to build, "all" to build all targets
                -d          Set cmake variables
                -def        Execute scripts with default values (same as executing script with no arguments) 
                            [builds all targets, debug, default cmake variables]
            ''')

def main():
    cmd = ''
    sys.argv.remove(sys.argv[0])

    for c in sys.argv:
        cmd += c + ' '

    cmdList = cmd.split(' ')
    target = 'all'
    conf = 'Debug'
    val = ''

    shouldConfigure = False
    shouldBuild = False

    try:
        if '-config' in cmd:
            shouldConfigure = True
        elif '-build' in cmd:
            shouldBuild = True
            conf = cmdList[cmdList.index('-build') + 1]
            if ('-' in conf): # check if the configuration value is empty then set default value for configuration 
                conf = 'Debug'
            if '-t' in cmd:
                target = cmdList[cmdList.index('-t') + 1]
        elif '-def' in cmd:
            config('')
            build()
            exit()
        elif '-h' in cmd:
            help()
        elif len(sys.argv) == 0:
            config('')
            build()
            exit()
        else:
            raise Exception

        # execute commands
        if shouldConfigure:
            config(val)
        if shouldBuild:
            build(conf, target) 

    except Exception:
        print('Arguments not valid!')
        help()

if __name__ == '__main__':
    main()
