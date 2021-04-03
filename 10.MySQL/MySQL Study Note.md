数据库：为实现一定目的，按某种规则组织起来的数据的集合。简单说，数据库是存储数据的库。  
数据库的作用：管理和存储海量数据，便于程序开发  
  
# 1. SQL、DB、DBMS的关系  
    1). DB：database，数据库   
    2). DBMS：数据监控管理系统，常见的有MySql，Oracle，DB2，SQLServer  
    3). SQL：结构化查询语言，是一门标准通用的余元。标准的sql适合于所有的数据库产品。  
        SQL属于高级语言，SQL语句在执行的时候，实际上内部也会先进性编译，然后再执行sql（sql语句的编译由DBMS完成）  
  
DBMS负责执行SQL语句，通过执行SQL语句来操作DB中的数据。  
  
# 2. 什么是表  
表：table，是数据库的基本组成单元，所有的数据都以表格的形式组织，目的是可读性强。  
    一个表包括行和列，行称为数据/记录（data），列被称为字段（column）  
每个字段包括的属性：字段名，数据类型，相关的约束  
  
# 3. SQL语言介绍  
常见的SQL语句类型  
(1). 数据定义语言DDL：create drop alter，对表结构的增删改  
(2). 数据操作语言DML：INSERT, UPDATE, DELETE， 对表数据的增删改  
(3). 数据查询语句DQL：凡是SELECT语句都是DQL  
(4). 事务处理语言TPL：grant授权，revoke撤销权限    
(5). 数据控制语言DCL：commit提交事务，rollback回滚事务  
  
# 4. 常用命令   
  
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
  
# 5. 简单的查询语句（DQL）  
    1). 语法格式：select 字段名1，字段名2，字段名3，... from 表名;  
    2). 字段名可以参与数学运算，比如  查询年薪：select ename,sal*12 from emp;  
    3). 可以给查询结构的列重命名, 比如 查询年薪：select ename,sal*12 as year_sal rom emp; （as关键字可以省略）  
    4). SQL语句中 字符串 用单引号括起来！！  
    5). 查询全部字段：select * from 表名;  
  
# 6. 条件查询  
## 1). 语法格式：  
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
## 2). 条件查询  
        等于=  
        不等于!= 或<>  
        between...and...在两个数范围之间（闭区间）   
        is null 为null  
        and  并且  
        or  或者  
        in  包含，相当于多个or  
        not in  不在这个范围中  
        like  模糊查询，支持 % 或 下划线 匹配  
## 3). is null 为空（注意，数据库中NULL不是一个值，表示什么也没有，为空，不能用等号衡量）  
        is not null 不为空   
        Example: 1. 查询哪些员工没有津贴：select ename from emp where comm is null;  
## 4). and和or的优先级  
```
        Example：1. 找出工资大于1000并且部门编号是20或30部门的员工：  
                    select ename, sal, deptno from emp where sal > 1000 and deptno = 20 or deptno = 30;  （错误！）  
                    select ename, sal, deptno from emp where sal > 1000 and (deptno = 20 or deptno = 30);（正确！）  
```
        注意：运算符优先级不确定时，加小括号  
## 5). in 等同于多个or  
        not in 不在括号指定的内容当中  
        Example: 1. 找出工作岗位是MANAGER或SALESMAN的员工  
                    select ename, job from emp where job = 'MANAGER' or job = 'SALESMAN';    
                    select ename, job from emp where job in ('MANAGER', 'SALESMAN');  
## 6). like，模糊查询  
        %：任意多个字符  
        _: 任意一个字符  
        Example：1. 找出名字中含有'O'的员工：select ename from emp where ename like '%O%';  
                 2. 找出名字中第二个字母是'A'的员工：select ename from emp where ename like '_A%';  
                 3. 找出名字中有下划线的员工：select ename from emp where ename like '%\_%'; 转义字符'\'  
# 7. 排序（升序、降序）  
## 1). 语法格式：   
        select   
            字段1， 字段2，.....  
        from   
            表名  
        order by  
            排序条件;（默认升序， asc表示升序，desc表示降序）   
## 2). 注意：多个字段同时排序时，越靠前的字段的主导作用越大。只有前面字段经过排序后仍旧相同的情况下，后面的排序才起作用。  
  
    Example: 1. 按照工资升序，找出员工名和薪资：select ename, sal from emp order by sal;      (默认升序)  
                                             select ename, sal from emp order by sal asc;  (指定升序)  
                                             select ename, sal from emp order by sal desc; (指定降序)  
             2. 按照工资的降序排列，当工资相同时，再按照名字的升序排列：  
                select ename, sal from emp order by sal desc, ename asc;(指定工资降序，名字升序)  
                select ename, sal from emp order by sal desc, ename;    (指定工资降序，名字默认升序)  
## 3). order by 后的排序条件可以根据前面指定的字段的顺序来表示： 
    Example：1. select ename, sal from emp order by 1; (按照ename升序排)  
             2. select * from emp order by 1, 2 desc; (按照第一字段升序，第二个字段降序)  
## 4). 从指定表中查询满足某条件的项目，再进行排序  
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
  
# 8. 分组函数 (也叫 多行处理函数， 输入多行，输出一行)  
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

# 9. 单行处理函数：输入多少行数据，就输出多少行  
ifnull()：空处理函数   
        ifnull(可能为null的数据，被当作什么来处理)  
        Example：1.计算每个员工的年薪：select ename, (sal+comm)*12 from emp; (注意：只要运算式子中有NULL，运算结果也会是NULL)  
                                     select ename, (sal + ifnull(comm, 0))*12 from emp; (如果comm为null，视comm为0)  
                 2. select ename, ifnull(comm, 0) from emp; 查询员工名字，如果comm为null，则视comm为0  
  
# 10. group by 和 having  
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
# 11. 去除重复记录    
    select distinct job from emp;   
    注意：distinct只能出现在所有字段的最前面    
    select distinct 字段1，字段2，...， from emp; 所有字段联合去重    
  
    Example：1. 统计岗位的数量：select count(distinct job) from emp; // 取出job中的重复记录，然后统计数量    
  
# 12. 一个完整的DQL语句该怎么写？    
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
# 13. 关于表的别名：  
    select e.ename from emp e;  
  
# 14. 连接查询    
## 14.1. 连接查询：在实际开发中，大部分情况下都不是从单表中查询数据，一般都是多张表联合查询取出最终的结果。    
                   实际开发中，一般一个业务都会对应多张表，比如学生和班级，至少两张表。  如果学生和班级存储到一张表中，数据会存在大量重复，导致数据冗余。    
## 14.2. 连接查询的分类：  
        根据表的连接方式，分为：  
            内连接  
                等值连接  
                非等值连接  
                自连接  
            外连接  
                左外连接（左连接）  
                右外连接（右连接）  
            全连接（略）    
## 14.3. 表的连接查询方面有一种现象被称为：笛卡尔积现象（笛卡尔乘积现象）   
    笛卡尔积现象：当两张表进行连接查询时，没有任何条件限制，最终的查询结果条数是两张表记录条数的乘积。    
    案例：找出每一个员工的部门名称，要求显示员工名和部门名。   
    select ename, dpetno from emp, dept; 会产生56条记录，因为没有条件约束，查询结果是两张表中记录条数的乘积，emp中有14个记录，dept中有4个，14*4=56   
  
## 14.4. 如果避免笛卡尔积现象：加条件限制    
        增加条件后，不会减少匹配次数，但只会显示有效记录。    
  
    案例：找出每一个员工的部门名称，要求显示员工名和部门名。   
        select   
            e.ename, d.dname   
        from   
            emp e, dept d  
        where   
            e.deptno = d.deptno;  
  
## 14.5. 内连接之等值连接：最大的特点是  条件是等量关系  
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
## 14.6. 内连接之非等值连接：最大特点是  连接条件中的关系是非等量关系  
        案例： 找出每个员工的工资等级，要求显示员工名、工资和工资等级      
            select   
                e.ename, e.sal, s.grade  
            from   
                emp e  
            inner join // inner 可以省略  
                salgrade s  
            on   
                e.sal between s.losal and s.hisal;  
## 14.7. 自连接，最大特点是：一张表看做两张表，自己连自己  
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
  
## 14.8. 外连接  
### (1). 什么是外连接？与内连接的区别  
        内连接：假设A和B进行连接，使用内连接的话，凡是A表和B表能够匹配上的记录查询出来，这就是内连接。AB两张表没有主副之分，两张表是平等的。  
        外连接：假设A和B进行连接，使用外连接的话，AB两张表中有一张是主表，一张是副表，主要查询主表中的数据，捎带着查询副表。当副表中的数据没有和主表中的数据匹配上，副表自动模拟出NULL与之匹配。  
  
### (2). 外连接分类  
        左外连接（左连接）：左边的表是主表  
        右外连接（右连接）：右边的表是主表  
        注意：左连接有右连接的写法，右连接也有左连接的写法。  
  
### (3). 外连接最重要的特点：主表的数据无条件的全部查询  
  
#### 案例1：找出每一个员工的上级领导（所有员工必须全部查询）  
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
#### 案例2：找出那个部门没有员工？    ---- 要查询所有部门，所以要以部门表dept为主表  
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
      
## 14.9. 三张表如何连接查询？  
#### 案例1：找出每个员工的部门名称和工资等级 
``` 
        ...  
            A  
        join  
            B  
        join  
            C  
        on  
            ...  
```
        表示A表先和B表进行表连接，连接之后A表继续和C表进行连接。（或者说A和B的连接结果，继续和C连接）  
```  
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
```
#### 案例2：找出每个员工的部门名称和工资等级、上级领导  
```
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
```
# 15. 子查询  
## 15.1. 什么是子查询：select语句中嵌套select语句，被嵌套的select与是子查询  
          子查询可以出现在哪里：  
            select  
                ..(select).  
            from  
                ..(select).  
            where  
                ..(select).  
#### Example 1. from后面子查询  
    找出每个部门的平均薪资的薪资等级  
             1. 找出每个部门的平均薪资： select  deptno, avg(sal) from emp group by deptno;  
             2. 将以上查询结果当作临时表t，让t表和salgrade表连接，条件是t.avgsal between s.losal and s.hisal;  
```
            select   
                t.*, s.grade   
            from   
                (select  deptno, avg(sal) as avgsal from emp group by deptno) t  
            join   
                salgrade s   
            on   
                t.avgsal between s.losal and s.hisal;  
```
#### Example 2. 找出每个部门平均的薪资等级  
         1. 找出每个员工的薪水等级：select e.ename, e.sal, e.deptno, s.grade from emp e join salgrade s on e.sal between s.losal and s.hisal;  
         2. 基于以上结果，继续按照deptno分组，求grade平均值  
        select   
            e.deptno, avg(s.grade)  
        from   
            emp e  
        join   
            salgrade s  
        on  
            e.sal between s.losal and s.hisal  
        group by  
            e.deptno;   
## 3. select后面子查询  
#### Example: 找出每个员工所在的部门名称，要求显示员工名和部门名  
        select e.ename, d.dname from emp e join dept d on e.deptno = d.deptno;  
        select e.ename, (select d.dname from dept where e.deptno = d.deptno)) as dname from emp e;  
# 16. union:可以将查询结果相加  
Example：找出工作岗位是SALESMAN和MANAGER的员工  
#####    方法1. 
```
select ename, job from emp where job in ('MANAGER', 'SALESMAN');   
```
#####    方法2. 
```
select ename, job from emp where job='MANAGER' or job='SALESMAN';  
```
#####    方法3：
```
    select ename, job from emp where job='MANAGER'  
    union  
    select ename, job from emp where job='SALESMAN';  
```
    两张不相干的表的数据拼接到一起显示  
    select ename from emop  
    union  
    select dname from dept; 
   
# 17. limit（重点， 以后分页查询全靠它）    
### (1) limit是mysql特有的，其他数据库没有，不通用。    
### (2) limit取结果中的部分数据    
### (3) limit是sql语句最后执行的一个环节    
```
    select     5    
        ...        
    from       1  
        ...    
    where      2   
        ...    
    group by   3  
        ...    
    having     4    
        ...      
    order by   6    
        ...    
    limit      7    
        ...    
```
### (4) 语法： limit startIndex, length // startIndex表示起始的位置, 0表示第一条数据；length表示取几个    
##### Example1. 取出工资前五名的员工（思路：降序取前5个）  
```
            select ename, sal from emp order by sal desc limit 0, 5;  
            select ename, sal from emp order by sal desc limit 5; // 默认从0开始  
```
##### Example2. 找出工资排名在第4~9的员工：    
```
            select ename, sal from emp order by sal desc limit 3, 6;  // 注意索引从0开始    
```
### (5) 通用的标准分页sql    
每页显示pageSize条记录， 那么第pageNo页：(pageNo-1)*pageSize, pageSize    
   
# 18. 创建表      
## 建表语句的语法格式：   
``` 
    create table 表名(    
        字段名1 数据类型,    
        字段名2 数据类型,    
        字段名3 数据类型,    
        ...    
    );   
```
表名在数据库中建议以t_或tbl_开头    
  
## MySql中常见的数据类型
    int      整数型     
    bigint   长整型    
    float    浮点型    
    char     定长字符串    
    varchar  可变长字符串      
    date     日期类型      
    BLOB     二进制大对象（存储图片、视频等流媒体信息）  Binary Large OBject    
    CLOB     字符大对象（存储较大文本，比如，可以存储4G的字符串） Character Large OBject    
  
### char和varchar的选择：    
    实际开发中，当某个字段中的数据长度不发生变化的时候，如型别、生日，都采用char    
    当一个字段的数据长度不确定，例如，简介、姓名采用varchar    
##### Example：   
```  
    创建学生表， 学生信息包括：  
        学号：bigint    
        姓名：varchar(255)    
        性别：char(1)     
        班级编号：varchar(255)  
        生日：char(10)  
    create table t_student(    
        no bigint,    
        name varchar(255),    
        sex char(1) default 1, // default字段指定默认值，如果没有插入，默认为1      
        classno varchar(255),   
        birth char(10)   
    );     
```
# 19. 插入数据    
语法格式： insert into 表名 (字段名1，字段名2，字段名3，...) values (值1，值2， 值3,...)   
要求：字段名的数据量必须和值的数量相同，并且数据类型要对应相同    
```
insert into tbl_student (no, name, sex, classno, birth) values (1, 'zhangsan', '1', 'Senior High 3', '1994.05.06');  
insert into tbl_student (name, sex, classno birth, no) values ('lisi', 'M', 'Senior High 3', '1995.10.20', 2);  
insert into tbl_student (name)values ('wangwu'); // 除name字段外，其余字段自动插入NULL    

// 字段名可以省略不写，但是后面的values有要求    
insert into tbl_student values (3, 'wangwu', 'M', 'Senior High 5', '1993.02.03'); // 值的顺序必须和表中字段名顺序一样    

// 一次插入多行数据，逗号隔开:    
insert into tbl_student (no, name, sex, classno, birth) values  
(4, 'zhaoliu', 'F', 'Senior High 4', '1993.06.03'),  
(5, 'wanger', 'M', 'Senior High 4', '1993.09.23'),  
(6, 'lihua', 'F', 'Senior High 2', '1995.12.03');  
```  
注意：当一条insert语句执行成功之后，表格中必然会多一条记录。    
  
# 20. 表的复制    
```
create table emp1 as select * from emp2; // 从emp2中复制select查询的结果到新表emp1中    
insert into emp1 select * from dept; // 把从dept查询的结果当数据插入到表emp1中    
```
# 21. 修改表中的数据    
语法格式： update 表名 set 字段名1=值1，字段名2=值2，... where 条件    
注意：没有条件，整张表数据全部更新    
  
##### Example：    
    1. 将学号为5的学生姓名改为'guowei'：select tbl_student set name = 'guowei' where no = 5;    
    2. 更新所有记录：update tbl_student set no = 10;  
  
# 22. 删除表中的数据    
语法格式： delete from 表名 where 条件;    
注意：没有条件则全部删除    
##### Example：    
    1. 删除学号为5的记录": delete from tbl_student where no = 5;    
  
#### 删除表：  
    drop table if exists tbl_student;   
  
#### 删除大表（重点）     
    delete删除数据效率慢，因为它并没有释放数据的存储空间（考虑到回滚）    
  
    truncate table 表名; // 表被阶段 ，不可回滚，永久丢失！！     
  
# 23. 修改表的结构
使用工具完成即可，因为在实际开发中，一旦表格设计好以后，对表结构的修改是很少的。    
  
# 24. 约束Constraint（重点）   
## 24.1. 什么是约束：保证数据的完整性、合法性、有效性。
每个学生学号是唯一的（唯一性约束），每个学生都有生日（非空约束）  
## 24.2. 常见的约束：  
* 非空约束(not null)：约束的字段不能为NULL  
* 唯一约束(unique)：约束的字段不能重复  
* 主键约束(primary key)：约束的字段既不能为NULL，也不能重复（简称PK）  
* 外键约束(foreign key)：简称FK  
* 检查约束(check):注意Oracle数据库有check约束，但是mysql没有，目前mysql不支持该约束。    
## 24.3. 非空约束 not null  
```
        create table t_user(  
            id int,  
            username varchar(255) not null,  
            password varchar(255)  
        );  
        insert into t_user (id, password) values (1, '123'); // 该插入会失败，因为username不能为NULL    
```
## 24.4. 唯一约束unique    
唯一约束修饰的字段具有唯一性，不能重复，但可以为NULL  
##### 案例1：给某一列添加唯一性约束      
 ```
        create table t_user(  
            id int,  
            username varchar(255) unique  
        );
        insert into t_user (1, 'zhangsan'),(2,'zhangsan'); // 报错，’zhangsan'重复  
        insert into t_user (1, 'zhangsan'), (2, NULL), (3, NULL); // success!  
```
#### 案例2：给两个字段添加唯一性约束  
        1. 多个字段联合起来加唯一性约束  
```
        create table t_user (
            id int,  
            usercode varchar(255),    
            username varchar(255),  
            unique(usercode, username)   // 表级约束
        );
        isnert into t_user values (1, '111','zs'); // success
        isnert into t_user values (2, '111','ls'); // success 
        isnert into t_user values (3, '222','zs'); // success
        isnert into t_user values (3, '222','zs'); // fail, 222-zs 重复
```
        2. 两个字段分别加unique约束  
```
        create table t_user (
            id int,  
            usercode varchar(255) unique,   // 列级约束  
            username varchar(255) unique
        );
        isnert into t_user values (1, '111','zs'); // success
        isnert into t_user values (2, '111','ls'); // fail, '111'重复 
        isnert into t_user values (3, '222','zs'); // fail， 'zs'重复
```
## 24.5. 主键约束（列级约束）  
```
    create table t_user(
        id int primary key,
        username varchar(255), 
        email varchar(255)
    );
    insert into t_user (id, username, email) values (1, 'zs', 'zs@123.com');
    insert into t_user (id, username, email) values (2, 'ls', 'ls@123.com');
    insert into t_user (id, username, email) values (3, 'ww', 'ww@123.com');

    insert into t_user (id, username, email) values (1, 'hanliu', 'hanliu@123.com'); // Error! 主键1重复
    insert into t_user ( username, email) values ('hanliu', 'hanliu@123.com');       // Error! 主键为NULL
```
id是主键，因为添加了主键约束，**主键字段中的数据不能重复，也不能为空**。一张表的主键约束只能有一个。 

### * 主键相关的术语  
##### 主键约束：primary key  
##### 主键字段：带有主键约束的字段  
##### 主键值：主键字段中的每一个值  
### * 主键的作用：  
##### 表的设计三范式中有要求，第一范式要求任何一张表都应该由主键。  
##### 主键的作用：主键值是这行记录在这张表中的唯一标识。  
### * 主键的分类：  
#### 根据主键字段的子弹数量来划分：
* 单一主键：推荐，常用的。  
* 复合主键：多个字段联合起来添加一个主键约束，复合主键不建议使用，违背三范式。  
#### 根据主键性质来划分：  
* 自然主键：主键值最好是一个与业务无关的自然数。  
* 业务主键：主键值和系统的业务挂钩。比如，银行卡卡号做主键，身份证号做主键。不推荐，最好不要使用和业务挂钩的字段作为主键。业务一旦改变，主键值可能会跟着变化，但有的时候没有办法变化，因为变化可能导致主键值重复。  

### * 使用表级约束定义主键
```
    create table t_user(
        id int, 
        username varchar(255),
        primary key(id)
    );

    insert into t_user(id,username) values (1, 'zs');
    insert into t_user(id,username) values (2, 'ls');
    insert into t_user(id,username) values (3, 'zww');

    insert into t_user(id,username) values (3, 'zl'); // 错误，主键重复
```
* mysql提供的主键值自增（重要！）  
```
    create table t_user(
        id int primary key auto_increment, // id字段自动维护一个自增的数字，从1开始，以1递增
        username varchar(255)
    );
    insert into t_user (username) values ('zs');
    insert into t_user (username) values ('ls');
    insert into t_user (username) values ('ww');
    insert into t_user (username) values ('zl');
```
## 24.6 外键约束 foreign key  
    业务背景：请设计数据库，用来维护学生和班级的信息  
    方案1：一张表存储所有数据。  --> 冗余，大量数据重复  
    方案2：两张表，班级表和学生表  
**顺序要求**：  
- 删除数据的时候，先删除子表，再删除父表；
- 添加数据的时候，先添加父表，再添加字表；
- 删除表的时候，先删除字表，再删除父表；
- 创建表的时候，先创建父表，再创建字表。

```
    create table t_class(
        cno int primary key,
        cname varchar(255)
    );

    create table t_student(
        sno int,
        sname varchar(255),
        classno int primary key,
        foreign key(classno) references t_class(cno) // 外键classno引用表t_class的con字段，表t_student的classno字段范围只能是t_class的con字段数据范围  
    );

    // 先插入父表，再插入子表
    insert intro t_class values(101,'dafdsvdsafdsafgds');
    insert intro t_class values(102,'ddafdsafdsarggdfd');

    insert into t_student values (1, 'zs1', 101);
    insert into t_student values (2, 'zs2', 101);
    insert into t_student values (3, 'zs3', 102);
    insert into t_student values (4, 'zs4', 102);
    insert into t_student values (5, 'zs5', 102);
```
注意：  
    1. 外键可以为NULL  
    2. 被引用的字段不一定是主键，但至少具有unique约束。   

# 25. 存储引擎  
MySql默认使用的存储引擎是InnoDB方式。MySql支持很多存储引擎，每一个存储引擎都对应了一种不同的存储方式。每一种存储引擎都有优缺点。

# 26. 事务 Transaction  
## 26.1. 什么是事务  
    一个事务是一个完整的业务逻辑单元，不可再分。  
    比如：银行账户转账，从A账户向B账户转账10000，需要执行两条sql语句：
```
    update t_act set balance = balance - 10000 where actno = 'act-001';
    update t_act set balance = balance + 10000 where actno = 'act-002';
```
    以上两条sql语句必须同时成功，或者同时失败，不允许出现一条成功，一条是失败。要想保证以上的两条DML语句同时成功或者同时失败，就需要使用数据库的事务机制。  
## 26.2. 和事务相关的只有DML语句 (insert, update, delete).  
    因为只有这三个语句和数据库中的数据相关，事务的存在是为了保证数据的完整性和安全性。

假设一个事情，需要先执行一条insert，再执行一条update，最后执行一条delete，这个事才算完成。

开启事务。

执行insert语句成功后，把这个执行记录到数据库的操作历史中，并不会向文件中保存一条数据，不会真正的修改硬盘上的数据。
执行update语句成功后，也会记录历史操作，但不会修改硬盘数据。delete同理。均只是记录到缓存。

提交事务或者回滚事务（结束）
提交或者回滚后，修改会同步到硬盘文件中，同时历史操作的缓存被清空。
## 26.3. 事务的特性
事务包括四大特性：ACID
* A - 原子性：事务是最小的工作单元，不可再分  
* C - 一致性：事务必须保证多条DML语句同时成功或者同时失败  
* I - 隔离性：事务A和事务B之间具有隔离  
* D - 持久性：最终数据必须持久化到硬盘文件中，事务才算成功的结束
## 26.4. 关于事务之间的隔离性
事务隔离性存在的隔离级别，理论上隔离级别包括4个：
* 第一级别：读未提交（read uncommitted），对方事务还未提交，当前事务可以读取到对方为提交的数据。读未提交存在**脏读**(dirty read)现象，表示读到了脏的数据。
* 第二级别：读已提交（read committed），对方事务提交之后的数据我方可以读取到。这种隔离界别解决了**脏读现象**。读已提交存在的问题是**不可重复读**。
* 第三级别：可重复读（repeatable read）,这种隔离级别解决了**不可重复读问题**。这种级别存在的问题是**读取到的数据是幻象**，对方已经修改了数据，而我方读取到的是之前的数据。
* 第四级别：序列化读/串行化读，解决了所有问题，但是效率低，需要排队。
**注意：**
# Oracle数据库默认的隔离级别是：读已提交；mysql默认的隔离级别是：可重复读。 
# mysql事务默认情况下是自动提交的，只要执行任意一条DML语句，就提交一次。 
如何关闭自动提交：start transaction;
# 27.数据库设计三范式
## 27.1. 什么是设计范式
设计表的依据，按照这三个范式设计的表不会出现设计冗余
## 27.2. 三范式
* 第一范式：任何一张表都必须有主键，并且每一个字段原子性不可再分
* 第二范式：建立在第一范式的基础上，所有非主键字段完全依赖主键，不能产生部分依赖（单一主键，不能是复合主键）
多对多，三张表，关系表两个外键
* 第三范式：建立在第二范式的基础上，所有非主键字段直接依赖主键，不能产生传递依赖
一对多，两张表，多的表加外键
