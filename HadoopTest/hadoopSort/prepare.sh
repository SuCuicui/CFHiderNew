time /home/xidian/hadoop/bin/hadoop jar /home/xidian/hadoop/hadoop-examples-1.0.4.jar teragen 10737418 terasort_input01

#使用Teragen来产生数据，示例如下：
#hadoop jar hadoop-*-examples.jar teragen 参数1 参数2
#teragen的参数解释：
#  参数1：表示要产生的数据的行数。Teragen每行数据的大小是100B。
#  要产生1G的数据，需要的行数=1024*1024*1024/100=10737418行
#  参数2 : 产生的数据放置的文件夹地址

