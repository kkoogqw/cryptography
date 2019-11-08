import time
import DLP_Algorithm as DLP

def main():
    # variable define:
    p = 5682549022748424631339131913370125786212509227588493537874673173634936008725904358935442101466555561124455782847468955028529037660533553941399408331331403379
    g = 2410497055970432881345493397846112198995088771364307195189734031205605186951241875096796459061741781667380437076874705300974836586165283741668656930807264789
    y_a = 973768284341326272301553751114322685324340805902069613339667142187801529585352406975030927008752571917079716318221077758236884342662829402529734009607531649
    y_b = 4149822765985031146554298777122732051870868431387323913747785791685310508836836283702926446817000114868007555717546362425841865173929670156568682745060708314
    n = 4309874666

    string = input("A. BSGS\nB. Pollard-Rho(quick)\n")
    if string == "A" or string == "BSGS":
        start_time = time.clock()
        x_a = DLP.BSGS(g, y_a, p)
        x_b = DLP.BSGS(g, y_b, p)
        msg = pow(g, (x_a * x_b), p)
        end_time = time.clock()
        print("Algorithm: Baby-Step-Giant-Step/Shanks")
        print("x_a = %d, x_b = %d\n share-message is: %d" %(x_a, x_b, msg))
        print("check result:")
        DLP.check_rsult(g, x_a, y_a, p)
        DLP.check_rsult(g, x_b, y_b, p)
        print("Run time:", end_time - start_time)
    elif string == "B" or string == "Pollard-Rho":
        start_time = time.clock()
        x_a = DLP.Pollard_Rho(g, y_a, p, n)
        x_b = DLP.Pollard_Rho(g, y_b ,p, n)
        msg = pow(g, (x_a * x_b), p)
        end_time = time.clock()
        print("Algorithm: Pollard-Rho")
        print("x_a = %d, x_b = %d\nshare-message is: %d" % (x_a, x_b, msg))
        print("check result:")
        DLP.check_rsult(g, x_a, y_a, p)
        DLP.check_rsult(g, x_b, y_b, p)
        print("Run time:", end_time - start_time)
    return

if __name__ == '__main__':
    main()