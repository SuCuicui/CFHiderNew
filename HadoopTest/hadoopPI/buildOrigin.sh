find bin/ -name "*.class" -type f -print -exec rm -rf {} \;
echo "ok1"

javac -cp .:$JAVA_HOME/jre/lib/rt.jar:$JAVA_HOME/jre/lib/jce.jar:$HADOOP_HOME/hadoop-core-1.0.4.jar:$HADOOP_HOME/hadoop-tools-1.0.4.jar:../../soot-lib/commons-logging-1.1.3.jar:../../soot-lib/commons-cli-1.2.jar:$HADOOP_HOME/lib/commons-cli-1.2.jar src/*.java -d bin/
echo "ok2"

cd bin/
jar -cfm originPI.jar ../a.txt ./
echo "ok3"
