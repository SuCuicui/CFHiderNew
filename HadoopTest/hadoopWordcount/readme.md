#0.prepare :start hadoop
cd ../hadoop/bin
./hadoop namenode -format
./hadoop start-all.sh

#1.prepare data
./prepare.sh

#2.running origin class files
./run-origin.sh

#3.transform origin class files to new one with SGX (only replace the conditions)
./replace-hadoop-SGX-transformer.sh
#runing this new files
./run-replace.sh

#4.transform origin class files to new one with SGX (insert 30% fake conditions)
./30-fake-hadoop-SGX-transformer
#runing this new files
./30-run-fake.sh