#!/bin/bash

function runInAPPSFO() {
    cd ~/APPSFO
    echo "" >> ~/.bashrc
    echo "# alias pour l'APP SFO" >> ~/.bashrc
    echo "alias lilas='java -jar /home/commetud/3eme\ Annee\ MIC/APPSFO/LILASHOME/lib/lilasV4.jar -config=$PWD/lilasConfig.xml '"  >> ~/.bashrc
    echo "" >> ~/.bashrc
    echo "export PATH=/usr/local/Xilinx134.old/13.4/ISE_DS/ISE/bin/lin:/usr/local/jdk1.7.0_45/bin:$PATH" >> ~/.profile
    echo "export LM_LICENSE_FILE=2100@srv-gei-ens1" >> ~/.profile
    echo "export XILINXD_LICENSE_FILE=2100@srv-gei-ens1" >> ~/.profile
    java -jar /home/commetud/3eme\ Annee\ MIC/APPSFO/LILASHOME/lib/lilasV4.jar
    echo "Mettez à jour votre terminal avec"
    echo "$ source ~/.bashrc "
    echo "Testez lilas avec la commande"
    echo "$ lilas -version"
    echo "Testez l'installation de java avec le premier TP"
	echo "$ cd ~/APPSFO ; lilas /arch/processeurComplet/ProcesseurComplet2015.lilas -awt=coeurAWT -test -script=initSimuCtr"
}

mkdir ~/APPSFO
runInAPPSFO
