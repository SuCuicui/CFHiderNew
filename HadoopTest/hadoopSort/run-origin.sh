#使用Terasort排序
#使用terasort对刚才使用teragen产生的数据进行排序，排序结果输出到/user/hadoop/terasort/1T-output。
#默认的reduce数目是1，会导致任务跑得非常慢。通过-Dmapred.reduce.tasks指定reduce数目，这里我们设置50个
#hadoop jar hadoop-*-examples.jar terasort -Dmapred.reduce.tasks=50 \
#/user/hadoop/terasort/1T-input /user/hadoop/terasort/1T-output

/home/xidian/hadoop/bin/hadoop dfs -rmr /user/xidian/terasort_output01

time /home/xidian/hadoop/bin/hadoop jar /home/xidian/hadoop/hadoop-examples-1.0.4.jar terasort terasort_input01 terasort_output01
