#!/usr/bin/env python3
import pid

def main():
    ##---------- CONTROLLER SETUP ----------##
    ## Instantiate PID controller
    controller = pid.PID()
    ## Set proportional gain
    controller.Kp = 10.0
    ## Set integral gain
    controller.Ki = 1.0
    ## Set derivative gain
    controller.Kd = 2.0

    ##---------- EXAMPLE SETUP ----------##
    ## Pre-generate example dt values
    dts = (0.11, 0.12, 0.11)
    ## Pre-generate example error values
    errors = (9.8, 7.6, 5.4)

    ##---------- CONTROLLER EXAMPLE USAGE ----------##
    ## Enter control loop
    for i in range(3):
        ## Set current delta time
        controller.dt = dts[i]
        ## Execute controller
        output = controller(errors[i])
        ## Print control loop
        print(f'----------  LOOP {i}  ----------')
        print(f'controller.Kp  : {controller.Kp}')
        print(f'controller.Ki  : {controller.Ki}')
        print(f'controller.Kd  : {controller.Kd}')
        print(f'controller.dt  : {controller.dt}')
        print(f'error[i]       : {errors[i]}')
        print(f'output(error)  : {output}')
        print(f'get_prev_error : {controller.get_prev_error()}')
        print(f'get_total_error: {controller.get_total_error()}')

if __name__ == '__main__':
    main()
