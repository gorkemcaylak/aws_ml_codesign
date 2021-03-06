#===============================================================#
#                                                               #
#                       	run5.sh                         	#
#                                                               #
#   A bash script to run and collect for K_CONST from 1 to 5	#
#																#
#                                                               #
#===============================================================#


#!/bin/bash

# set up emulation configuration
echo "#################################################"
echo " Setting emulation configuration..."
echo "#################################################"
export  XCL_EMULATION_MODE=true
emconfigutil --xdevice=xilinx:adm-pcie-7v3:1ddr:3.0

# the directory of this lab
app_dir=`pwd`

# make results directory to store the results
if [ ! -d ./results ]; then
	mkdir results
fi
# create a file to store all the estimate reports
echo "####################################################" > ./results/estimates_summary.xtxt
echo " Summary of Estimate Reports for K_CONST from 1 to 5" >> ./results/estimates_summary.xtxt
echo "####################################################" >> ./results/estimates_summary.xtxt
echo "" >>./results/estimates_summary.xtxt
echo "" >>./results/estimates_summary.xtxt


# loops for K_CONST from 1 to 5 
for index in 1 2 3 4 5
do 
	### COMPILATION
	# create some blank-line space for easy readability
	echo ""; echo ""; echo "" ; echo ""
	echo "####################################################"
	echo " Compiling project with K_CONST=$index"
	echo "####################################################"
	make clean
	make ocl OCL_TARGET=sw_emu APPLICATION_DIR=$app_dir OCL_DEVICE=xilinx:adm-pcie-7v3:1ddr:3.0 K_CONST=$index

	### EXECUTION
	echo ""; echo ""; echo "" ; echo ""
	echo "####################################################"
	echo " Executing DigitRec with K_CONST=$index"
	echo "####################################################"
	./DigitRec_host.exe -f DigitRec.sw_emu.xclbin 

	### COLLECTING RESULTS
	echo "####################################################" >> ./results/estimates_summary.xtxt
	echo -e "Estimate Report with K_CONST=$index" >> ./results/estimates_summary.xtxt
	echo "####################################################" >> ./results/estimates_summary.xtxt
	cat system_estimate.xtxt >> ./results/estimates_summary.xtxt
	echo "" >>./results/estimates_summary.xtxt 
	echo "" >>./results/estimates_summary.xtxt 
	echo "" >>./results/estimates_summary.xtxt 

done

# clean up
rm system_estimate.xtxt
