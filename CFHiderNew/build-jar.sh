javac -classpath ../soot-lib/log4j-1.2.11.jar:../soot-lib/commons-io-2.4.jar:../soot-lib/symja-2015-09-26.jar:../soot-lib/soot-trunk.jar -d bin/ src/*.java
cd bin/
jar -cfm ../testcase.jar ../META-INF/MANIFEST.MF ./

