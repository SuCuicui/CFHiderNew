find 100TransFakeSegmentForJni/ -name "*.class" -type f -print -exec rm -rf {} \;
find 100TransFakeSegmentForJni/ -name "*.jar" -type f -print -exec rm -rf {} \;

java -Xms512M -Xmx1024M -cp /home/xidian/Development/soot-lib/symja-2015-09-26.jar:/home/xidian/Development/soot-lib/jasminclasses-custom.jar:/home/xidian/Development/soot-lib/polyglotclasses-1.3.5.jar:/home/xidian/Development/soot-lib/soot-trunk.jar:/home/xidian/Development/soot-lib/commons-io-2.4.jar:/home/xidian/Development/soot-lib/log4j-1.2.11.jar:/home/xidian/Development/output/testcase01.jar  LoggerMain100 -allow-phantom-refs -cp .:/usr/lib/jvm/java-7-openjdk-amd64/jre/lib/rt.jar:/usr/lib/jvm/java-7-openjdk-amd64/jre/lib/jce.jar:/home/xidian/hadoop/hadoop-core-1.0.4.jar:/home/xidian/hadoop/hadoop-tools-1.0.4.jar:/home/xidian/Development/soot-lib/commons-logging-1.1.3.jar:/home/xidian/Development/soot-lib/commons-cli-1.2.jar:/usr/local/hadoop/hadoop-core-1.0.4.jar:/home/xidian/hadoop/lib/commons-cli-1.2.jar -src-prec c -f c -include-all -process-dir /home/xidian/hadoop-tsetcase/hadoopWordcount/bin -output-dir /home/xidian/hadoop-tsetcase/hadoopWordcount/100TransFakeSegmentForJni

cd 100TransFakeSegmentForJni/

jar -cfm 100TransFakeSegmentForJni.jar a.txt FakeSegmentForJni/ pegasus/

echo "ok"
