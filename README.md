DcpStat
=======

Emulate collect and display DCP status

准备工作
- 安装VC2010
- 安装nodejs，并加入到系统环境变量PATH中，
- 安装git客户端，
- 建议安装mingw，若安装的是mingw git，那么不用额外安装mingw

编译和配置

- 进入NativeStat，
- 打开dcp_stat.sln编译Debug X64

- 在mingw或者命令行下进入DcpStat.node
- node-gyp configure -d
- 进入build目录,打开binding.sln，编译 Debug X64

- 进入EmuStat
- 打开emustat.sln，编译Debug win32

- 进入Server
- 运行npm install安装依赖的库文件
- 编辑app.js，修改servAddr为服务器的ip

运行
- 运行EmuStat\Debug\EmuStat.exe
- 进入server，运行node app.js
- 打开浏览器，输入地址http://127.0.0.1:3000
- 127.0.0.1可以修改为配置的servAddr的值
