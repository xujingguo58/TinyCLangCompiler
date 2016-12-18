# TinyCLangCompiler
##一个简单的C语言文法编译器，目标是实现编译器前后端，并且具有GUI。
##具体实现变量声明、赋值语句、条件语句（if、while）、算数逻辑运算。
  设计流程是先设计文法，然后语法分析得到token序列、再语法分析判断目标程序是否有语法错误，然后进行语义分析即中间代码生成，生成四元式，
  并在此过程中完成分析表。至此，前端工作完成。
  如果还有时间，再进行优化和目标代码生成，翻译成汇编语言。
  以上才做在控制台应用程序中完成，完成后封装成函数，添加到windows窗体应用程序。
  实现GUI，如果可以的话，让汇编在DOSBox里运行，真正实现完整的编译器。
