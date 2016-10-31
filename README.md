# Seca

entrar no search:
ssh axxxxx@search1.di.uminho.pt 

entrar compute:
qsub -I -qcpd -lnodes=1,walltime=60:00


enviar ficheiros pro search: scp nome axxxxx@search1.di.uminho.pt:nome

enviar pastas 
scp -r nome axxxxx@search1.di.uminho.pt:nome

carregar modulo:
module load gnu/4.9.0
