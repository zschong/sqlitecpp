# sqlitecpp
sqlite c++98 api wrap{open,exec,close,begin,commit,filename,errcode,backup,copy,operator=,column,row,result}

# API封装说明
## Open(const string& fname)
  打开数据库文件fname
## Copy(const Sqlite& dest)
  复制当前数据库到dest
## Exec(const string& sql)
  执行SQL语句sql
## Close()
  关闭当前数据库
## Backup(const string& fname)
  保存当前数据库到fname文件
## Begin()
  开始批量SQL
## Commit()
  提交批量SQL
## operator=(const sqlite& src)
  赋值运算符重载，把src内容复制到当前数据库
## GetName()
  获取当前数据库文件名
## GetErrorMessage()
  获取当前错误信息
## GetErrorCode()
  获取当前错误码
