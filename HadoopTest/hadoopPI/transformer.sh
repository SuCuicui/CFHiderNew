find sootOutput/ -name "*.class" -type f -print -exec rm -rf {} \;
find sootOutput/ -name "*.jar" -type f -print -exec rm -rf {} \;
echo "ok1"

java -Xms512M -Xmx1024M -cp ../../soot-lib/symja-2015-09-26.jar:../../soot-lib/jasminclasses-custom.jar:../../soot-lib/polyglotclasses-1.3.5.jar:../../soot-lib/soot-trunk.jar:../../soot-lib/commons-io-2.4.jar:../../soot-lib/log4j-1.2.11.jar:../../CFHiderNew/testcase.jar  MyMain -allow-phantom-refs -cp .:$JAVA_HOME/jre/lib/rt.jar:$JAVA_HOME/jre/lib/jce.jar:$HADOOP_HOME/hadoop-core-1.0.4.jar:$HADOOP_HOME/hadoop-tools-1.0.4.jar:../../soot-lib/commons-logging-1.1.3.jar:../../soot-lib/commons-cli-1.2.jar:$HADOOP_HOME/hadoop-core-1.0.4.jar:$HADOOP_HOME/lib/commons-cli-1.2.jar -src-prec c -f c -include-all -process-dir ./bin -output-dir ./sootOutput
echo "ok2"

cd sootOutput/
jar -cfm transformedPI.jar ../a.txt testPI/ invoker/
echo "ok3"


MyMain --d /home/xidian/CFHiderNew/HadoopTest/hadoopPI/sootOutput --cp /usr/lib/jvm/jdk1.7.0_79/jre/lib/jfr.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/localedata.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/dnsns.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/sunec.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/zipfs.jar:/home/xidian/hadoop-1.0.4/hadoop-tools-1.0.4.jar:/home/xidian/CFHiderNew/HadoopTest/hadoopPI/bin/:/usr/lib/jvm/jdk1.7.0_79/jre/lib/resources.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/jce.jar:/home/xidian/hadoop-1.0.4/lib/commons-cli-1.2.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/sunjce_provider.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/rt.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/sunpkcs11.jar:/home/xidian/hadoop-1.0.4/hadoop-core-1.0.4.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/jsse.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/charsets.jar::/home/xidian/CFHiderNew/HadoopTest/hadoopPI/bin/:/usr/lib/jvm/jdk1.7.0_79/jre/lib/resources.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/rt.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/jsse.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/jce.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/charsets.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/jfr.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/sunec.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/sunpkcs11.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/sunjce_provider.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/zipfs.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/dnsns.jar:/usr/lib/jvm/jdk1.7.0_79/jre/lib/ext/localedata.jar:/home/xidian/hadoop-1.0.4/lib/commons-cli-1.2.jar:/home/xidian/hadoop-1.0.4/hadoop-core-1.0.4.jar:/home/xidian/hadoop-1.0.4/hadoop-tools-1.0.4.jar --xml-attributes invoker.sgx_invoker testPI.PiEstimator testPI.PiEstimator$HaltonSequence testPI.PiEstimator$PiMapper testPI.PiEstimator$PiReducer 


