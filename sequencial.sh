#!/bin/bash

echo "System"
echo ""  
echo "Processador - cat /proc/cpuinfo"
echo ""  
cat /proc/cpuinfo 
echo ""  
echo "Processador - lscpu"
echo ""  
lscpu 
echo ""  
echo "Memory"  
echo ""  
cat /proc/meminfo 
echo ""  

echo "REP 1"  

echo "1 thread"  
~/pcp/pcpTrabalho1/heatSimulatorSequencial 0.001 testeSequencial.txt 1 

echo "REP 2"  

echo "1 thread"  
~/pcp/pcpTrabalho1/heatSimulatorSequencial 0.001 testeSequencial.txt 1


echo "REP 3"  

echo "1 thread"  
~/pcp/pcpTrabalho1/heatSimulatorSequencial 0.001 testeSequencial.txt 1
echo "" 

echo "REP 4"

echo "1 thread"
~/pcp/pcpTrabalho1/heatSimulatorSequencial 0.001 testeSequencial.txt 1
echo ""

echo "REP 5"

echo "1 thread"
~/pcp/pcpTrabalho1/heatSimulatorSequencial 0.001 testeSequencial.txt 1
echo ""
