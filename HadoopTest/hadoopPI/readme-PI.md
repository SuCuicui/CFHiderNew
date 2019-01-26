#0.prepare :start hadoop
cd ../hadoop/bin
./hadoop namenode -format
./hadoop start-all.sh

#1.running origin class files
./run-origin.sh

#2.transform origin class files to new one with SGX (only replace the conditions)
./replace-hadoop-SGX-transformer.sh
#encrypt SGXindex
./encrypt_SXGindex.sh
#runing this new files
./run-replace.sh

#3.transform origin class files to new one with SGX (insert 30% fake conditions)
./fake-hadoop-SGX-transformer.sh
#encrypt SGXindex
./encrypt_SXGindex.sh
#runing this new files
./run-fake.sh