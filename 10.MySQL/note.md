数据库：为实现一定目的，按某种规则组织起来的数据的集合。简单说，数据库是存储数据的库。
数据库的作用：管理和存储海量数据，便于程序开发

1. SQL、DB、DBMS的关系
    1). DB：database，数据库
    2). DBMS：数据监控管理系统，常见的有MySql，Oracle，DB2，SQLServer
    3). SQL：结构化查询语言，是一门标准通用的余元。标准的sql适合于所有的数据库产品。
        SQL属于高级语言，SQL语句在执行的时候，实际上内部也会先进性编译，然后再执行sql（sql语句的编译由DBMS完成）

DBMS负责执行SQL语句，通过执行SQL语句来操作DB中的数据。

2. 什么是表
表：table，是数据库的基本组成单元，所有的数据都以表格的形式组织，目的是可读性强。
    一个表包括行和列，行称为数据/记录（data），列被称为字段（column）
每个字段包括的属性：字段名，数据类型，相关的约束

3. SQL语言介绍
常见的SQL语句类型
(1). 数据定义语言DDL：create drop alter，对表结构的增删改
(2). 数据操作语言DML：INSERT, UPDATE, DELETE， 对表数据的增删改
(3). 数据查询语句DQL：凡是SELECT语句都是DQL
(4). 事务处理语言TPL：grant授权，revoke撤销权限
(5). 数据控制语言DCL：commit提交事务，rollback回滚事务

4. 常用命令 

\c   命令，终止一条语句
exit 退出MySQL

查看有哪些数据库：show databases;
创建自己的数据库：create database mydatabase;
使用指定数据库的数据：use mydatabase;
查询当前使用的是哪个数据库：select database();
查看数据库版本：select version();
查看当前数据库中有哪些表格：show tables;
查看表结构：desc 表名;
查看指定数据库中的有哪些表格：show tables from database_name;
删库跑路：drop database mydatabase;


初始化数据：source sql脚本文件;   （注意：直接使用source命令可以执行sql脚本）
以sql结尾的文件，该文件中编写了大量的sql语句，这样的文件为sql脚本。


查看创建某个表的语句：show create table 表名字;

5. 简单的查询语句（DQL）
    1). 语法格式：select 字段名1，字段名2，字段名3，... from 表名;
    2). 字段名可以参与数学运算，比如  查询年薪：select ename,sal*12 from emp;
    3). 可以给查询结构的列重命名, 比如 查询年薪：select ename,sal*12 as year_sal rom emp; （as关键字可以省略）
    4). SQL语句中 字符串 用单引号括起来！！
    5). 查询全部字段：select * from 表名;

6. 条件查询
    1). 语法格式：
            select 字段，字段，...
            from   表名
            where  条件;
        执行顺序：先from，然后where，最后select

        Example: 1. 查询工资等于5000的员工姓名，select ename from emp where sal = 5000;
                 2. 查询Smith的工资：select sal from emp where ename = 'Smith';（字符串 用单引号括起来）
                 3. 找出工资高于3000的员工：select ename, sal from emp where sal > 3000;
                 4. 查询工资 不等于 3000的信息：select ename, sal from emp where sal <> 3000;
                                              select ename, sal from emp where sal != 3000;
                 5. 查询工资在1100~3000之间的员工，包括1100和3000：select ename, sal from emp where sal >= 1100 && sal <= 3000;
                                                                select ename, sal from emp where sal >= 1100 and sal <= 3000;
                                                                select ename, sal from emp where sal between 1100 and 3000; // between...and...是 闭区间， 必须左小右大

    2). 条件查询
        等于=
        不等于!= 或<>
        between...and...在两个数范围之间（闭区间）
        is null 为null
        and  并且
        or  或者
        in  包含，相当于多个or
        not in  不在这个范围中
        like  模糊查询，支持 % 或 下划线 匹配
    3). is null 为空（注意，数据库中NULL不是一个值，表示什么也没有，为空，不能用等号衡量）
        is not null 不为空
        Example: 1. 查询哪些员工没有津贴：select ename from emp where comm is null;
    4). and和or的优先级
        Example：1. 找出工资大于1000并且部门编号是20或30部门的员工：
                    select ename, sal, deptno from emp where sal > 1000 and deptno = 20 or deptno = 30;  （错误！）
                    select ename, sal, deptno from emp where sal > 1000 and (deptno = 20 or deptno = 30);（正确！）
        注意：运算符优先级不确定时，加小括号
    5). in 等同于多个or
        not in 不在括号指定的内容当中
        Example: 1. 找出工作岗位是MANAGER或SALESMAN的员工
                    select ename, job from emp where job = 'MANAGER' or job = 'SALESMAN';
                    select ename, job from emp where job in ('MANAGER', 'SALESMAN');
    6). like，模糊查询
        %：任意多个字符
        _: 任意一个字符
        Example：1. 找出名字中含有'O'的员工：select ename from emp where ename like '%O%';
                 2. 找出名字中第二个字母是'A'的员工：select ename from emp where ename like '_A%';
                 3. 找出名字中有下划线的员工：select ename from emp where ename like '%\_%'; 转义字符'\'
7. 排序（升序、降序）
    1). 语法格式： 
        select 
            字段1， 字段2，.....
        from 
            表名
        order by
            排序条件;（默认升序， asc表示升序，desc表示降序）
    2). 注意：多个字段同时排序时，越靠前的字段的主导作用越大。只有前面字段经过排序后仍旧相同的情况下，后面的排序才起作用。

    Example: 1. 按照工资升序，找出员工名和薪资：select ename, sal from emp order by sal;      (默认升序)
                                             select ename, sal from emp order by sal asc;  (指定升序)
                                             select ename, sal from emp order by sal desc; (指定降序)
             2. 按照工资的降序排列，当工资相同时，再按照名字的升序排列：
                select ename, sal from emp order by sal desc, ename asc;(指定工资降序，名字升序)
                select ename, sal from emp order by sal desc, ename;    (指定工资降序，名字默认升序)
    3). order by 后的排序条件可以根据前面指定的字段的顺序来表示：
    Example：1. select ename, sal from emp order by 1; (按照ename升序排)
             2. select * from emp order by 1, 2 desc; (按照第一字段升序，第二个字段降序)
    4). 从指定表中查询满足某条件的项目，再进行排序
        select
            字段1， 字段2，.....
        from 
            表名
        where
            条件
        order by
            ......
    先指定from，再执行where，再执行select，最后执行order
    Example：1. 找出工作岗位是SALESMAN的员工，并且按照薪资的降序排列：
                select ename, job, sal from emp where job = 'SALESMAN' order by sal, desc;

8. 分组函数 (也叫 多行处理函数， 输入多行，输出一行)
    count 计数
    sum 求和
    avg 平均值
    max 最大值
    min 最小值

    注意：
        1. 所有分组函数都是对一组数据进行操作的。
        2. 分组函数自动忽略NULL
        3. count(*)和count(具体某个字段)的区别：
           count(*):总记录条数，与字段无关
           count(某个字段)：该字段中不为null的记录条数，自动忽略null
        4. 分组函数可以组合使用： select sum(sal), max(sal), min(sal), avg(sal) from emp;
    Example：1. 找出员工的工资总和：select sum(sal) from emp;
             2. 找出最高工资：select max(sal) from emp;
             3. 找出最低工资：select min(sal) from emp;
             4. 找出平均工资：select avg(sal) from emp;
             5. 找出总人数：  select count(*) from emp;
                             select count(ename) from emp; 
             6. 找出补助总数：select count(comm) from emp; 
                             等效于 select count(comm) from emp where comm is not null; 由于分组函数自动忽略null，因此后面的where条件可以不必加
             7. 找出工资高于平均工资的员工：
                错误输入：select ename from emp where sal > avg(sal); (无效地使用了分组函数：分组函数不可直接出现在where子句中)

9. 单行处理函数：输入多少行数据，就输出多少行
ifnull()：空处理函数
        ifnull(可能为null的数据，被当作什么来处理)
        Example：1.计算每个员工的年薪：select ename, (sal+comm)*12 from emp; (注意：只要运算式子中有NULL，运算结果也会是NULL)
                                     select ename, (sal + ifnull(comm, 0))*12 from emp; (如果comm为null，视comm为0)
                 2. select ename, ifnull(comm, 0) from emp; 查询员工名字，如果comm为null，则视comm为0

10. group by 和 having
    group by:按照某个字段或者某些字段进行分组
    having： 对分组之后的数据进行再次过滤，having是group by的搭档，只能跟在group by后面

        select
            xx
        from
            表名
        group by
            指定字段

    注意：
        1. 分组函数一般都会和group by联合使用，这是它为什么叫分组函数的原因
        2. 并且任何一个分组函数(max, min, avg, count, sum)都是在group by语句之后执行
        3. 当一条sql语句没有group by的话，整张表的数据会自成一组（会有缺省的group by）
        4. 分组函数不能出现在where子句中，因为group by在where执行之后才会执行，而分组函数在group by之后才会执行。

            select     5
                xx
            from       1
                ...    
            where      2    第一次过滤，满足where指定的条件
                ...
            group by   3    满足第一层条件的进行分组
                ... 
            having     4    再次过滤
                ...
            order by   6    最后排序
                ...  

    Example：1. 找出每个工作岗位的最高薪资：select max(sal) from emp group by job;
             2. 找出工资高于平均工资的员工：select ename, sal from emp where sal > (select avg(sal) from emp); 嵌套select，子查询
             3. 找出每个部门最高薪资，要求显示薪资大于2900的数据：
                3.1. 每个部门最高薪资： select max(sal), deptno from emp group by deptno;
                3.2. 薪资大于2900：select max(sal), deptno from emp group by deptno having max(sal) > 2900; 这种方式效率低
                select max(sal), deptno from emp where sal > 2900 group by deptno; 效率较高，建议能够使用where的地方尽量使用where
             4. 找出每个部门的平均薪资，要求显示薪资大于2000的数据：
                select deptno, avg(sal) from emp group by deptno having avg(sal) > 2000; 注意不能使用where，where后面不能使用分组函数
11. 去除重复记录  
    select distinct job from emp; 
    注意：distinct只能出现在所有字段的最前面  
    select distinct 字段1，字段2，...， from emp; 所有字段联合去重  

    Example：1. 统计岗位的数量：select count(distinct job) from emp; // 取出job中的重复记录，然后统计数量  

12. 一个完整的DQL语句该怎么写？  
            select     5
                xx
            from       1
                ...    
            where      2    第一次过滤，满足where指定的条件
                ...
            group by   3    满足第一层条件的进行分组
                ... 
            having     4    再次过滤
                ...
            order by   6    最后排序
                ...  
13. 关于表的别名：
    select e.ename from emp e;

14. 连接查询  
    14.1. 连接查询：在实际开发中，大部分情况下都不是从单表中查询数据，一般都是多张表联合查询取出最终的结果。  
                   实际开发中，一般一个业务都会对应多张表，比如学生和班级，至少两张表。  如果学生和班级存储到一张表中，数据会存在大量重复，导致数据冗余。  
    14.2. 连接查询的分类：  
        根据表的连接方式，分为：
            内连接
                等值连接
                非等值连接
                自连接
            外连接
                左外连接（左连接）
                右外连接（右连接）
            全连接（略）  
    14.3. 表的连接查询方面有一种现象被称为：笛卡尔积现象（笛卡尔乘积现象）
    笛卡尔积现象：当两张表进行连接查询时，没有任何条件限制，最终的查询结果条数是两张表记录条数的乘积。  
    案例：找出每一个员工的部门名称，要求显示员工名和部门名。 
    select ename, dpetno from emp, dept; 会产生56条记录，因为没有条件约束，查询结果是两张表中记录条数的乘积，emp中有14个记录，dept中有4个，14*4=56 

    14.4. 如果避免笛卡尔积现象：加条件限制  
        增加条件后，不会减少匹配次数，但只会显示有效记录。  

    案例：找出每一个员工的部门名称，要求显示员工名和部门名。 
        select 
            e.ename, d.dname 
        from 
            emp e, dept d 
        where 
            e.deptno = d.deptno;

    14.5. 内连接之等值连接：最大的特点是  条件是等量关系
        案例：查询每个员工的部门名称，要求显示员工名和部门名
        SQL92(旧语法):select e.ename, d.dname from emp e, dept d where e.deptno = d.deptno;
        SQL99: 结构清晰，表的连接条件和后来的where条件分离
            select
                e.ename, d.dname
            from 
                emp e
            join
                dept d
            on
                e.deptno = d.deptno;
        语法：
            select
                ...
            from 
                A
            (inner) join  // inner可以省略
                B
            on
                连接条件
            where
                ....
    14.6. 内连接之非等值连接：最大特点是  连接条件中的关系是非等量关系
        案例： 找出每个员工的工资等级，要求显示员工名、工资和工资等级  
            select 
                e.ename, e.sal, s.grade
            from 
                emp e
            inner join // inner 可以省略
                salgrade s
            on 
                e.sal between s.losal and s.hisal;
    14.7. 自连接，最大特点是：一张表看做两张表，自己连自己
    案例：找出每个员工的上级领导，要求显示员工名和对应的领导名字  
    
    两张表：一张是员工表，另一张是领导表，员工的领导编号 = 领导表的员工编号
            select
                a.ename as '员工名', b.ename as '领导名'
            from 
                emp a
            inner join 
                emp b
            on
                a.mgr = b.empno;

    14.8. 外连接
    (1). 什么是外连接？与内连接的区别
        内连接：假设A和B进行连接，使用内连接的话，凡是A表和B表能够匹配上的记录查询出来，这就是内连接。AB两张表没有主副之分，两张表是平等的。
        外连接：假设A和B进行连接，使用外连接的话，AB两张表中有一张是主表，一张是副表，主要查询主表中的数据，捎带着查询副表。当副表中的数据没有和主表中的数据匹配上，副表自动模拟出NULL与之匹配。

    (2). 外连接分类
        左外连接（左连接）：左边的表是主表
        右外连接（右连接）：右边的表是主表
        注意：左连接有右连接的写法，右连接也有左连接的写法。

    (3). 外连接最重要的特点：主表的数据无条件的全部查询

    案例1：找出每一个员工的上级领导（所有员工必须全部查询）
    左外连接的写法：
        select
            a.ename as '员工', b.ename as '领导'
        from 
            emp a // 左边，左边是主表
        left outer join
            emp b // 右边，右边是副表
        on
            a.mgr = b.empno;
    右外连接的写法：
        select 
            a.ename as '员工', b.ename as '领导'
        from 
            emp b
        right outer join   // outer可以省略
            emp a
        on 
            a.mgr = b.empno;

    案例2：找出那个部门没有员工？    ---- 要查询所有部门，所以要以部门表dept为主表
        select
            d.*
        from 
            emp e
        right join
            dept d
        on
            e.deptno = d.deptno
        where 
            e.empno in null; // 为null表示没有员工
    
    14.9. 三张表如何连接查询？
    案例1：找出每个员工的部门名称和工资等级
        ...
            A
        join
            B
        join
            C
        on
            ...
        表示A表先和B表进行表连接，连接之后A表继续和C表进行连接。（或者说A和B的连接结果，继续和C连接）

        select
            e.ename, d.dname, s.grade
        from 
            emp e
        join
            dept d
        on
            e.deptno = d.deptno
        join
            salgrade s
        on
            e.sal between s.losal and s.hisal;
    案例2：找出每个员工的部门名称和工资等级、上级领导
        select
            e.ename '员工', d.dname, s.grade, e1.ename '领导'
        from 
            emp e
        join
            dept d
        on
            e.deptno = d.deptno
        join
            salgrade s
        on
            e.sal between s.losal and s.hisal
        left join
            emp e1
        on
            e.mgr = e1.empno;
