Function: f_printf
BasicBlock: entry
Instruction 0x564adf050788 :  type(i32*) p0.addr  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf050800 :  type(void) ptr0x564adf050800  store  type(i32) p0 type(i32*) p0.addr 
Instruction 0x564adf050868 :  type(i32) ptr0x564adf050868  load  type(i32*) p0.addr 
Instruction 0x564adf04c2e8 :  type(i32) call  call  type(i8*) ptr0x564adf04a478  type(i32) ptr0x564adf050868  type(i32 (i8*, ...)*) printf 
Instruction 0x564adf0508b0 :  type(void) ptr0x564adf0508b0  ret  
ENDFunction

Function: printf
ENDFunction

Function: f_scanf_nop
BasicBlock: entry
Instruction 0x564adf050ae8 :  type(i32*) var0  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf050b78 :  type(i32) call  call  type(i8*) ptr0x564adf04a478  type(i32*) var0 type(i32 (i8*, ...)*) __isoc99_scanf 
Instruction 0x564adf050be8 :  type(i32) ptr0x564adf050be8  load  type(i32*) var0 
Instruction 0x564adf050c48 :  type(void) ptr0x564adf050c48  ret  type(i32) ptr0x564adf050be8  
ENDFunction

Function: __isoc99_scanf
ENDFunction

Function: f_rand
BasicBlock: entry
Instruction 0x564adf050dc8 :  type(i32*) var0  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf04b688 :  type(i32) call  call  type(i32 (...)*) rand 
Instruction 0x564adf050e40 :  type(void) ptr0x564adf050e40  store  type(i32) call type(i32*) var0 
Instruction 0x564adf050ea8 :  type(i32) ptr0x564adf050ea8  load  type(i32*) var0 
Instruction 0x564adf050f08 :  type(void) ptr0x564adf050f08  ret  type(i32) ptr0x564adf050ea8  
ENDFunction

Function: rand
ENDFunction

Function: func0
BasicBlock: entry
Instruction 0x564adf0511d8 :  type(i32*) p0.addr  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf051238 :  type(i32*) p1.addr  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf051298 :  type(i32*) var0  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0512f8 :  type(i32*) var1  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf051358 :  type(i32*) var2  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0513b8 :  type(i32*) var3  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf051418 :  type(i32*) var4  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf051478 :  type(i32*) var5  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0514d8 :  type(i32*) var6  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf051550 :  type(void) ptr0x564adf051550  store  type(i32) p0 type(i32*) p0.addr 
Instruction 0x564adf0515d0 :  type(void) ptr0x564adf0515d0  store  type(i32) p1 type(i32*) p1.addr 
Instruction 0x564adf04b618 :  type(i32) call  call  type(i32 ()*) f_rand 
Instruction 0x564adf051650 :  type(void) ptr0x564adf051650  store  type(i32) call type(i32*) var0 
Instruction 0x564adf04b5a8 :  type(i32) call1  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf0516d0 :  type(void) ptr0x564adf0516d0  store  type(i32) call1 type(i32*) var1 
Instruction 0x564adf04b538 :  type(i32) call2  call  type(i32 ()*) f_rand 
Instruction 0x564adf051750 :  type(void) ptr0x564adf051750  store  type(i32) call2 type(i32*) var2 
Instruction 0x564adf04b4a8 :  type(i32) call3  call  type(i32 ()*) f_rand 
Instruction 0x564adf051ff0 :  type(void) ptr0x564adf051ff0  store  type(i32) call3 type(i32*) var3 
Instruction 0x564adf04b438 :  type(i32) call4  call  type(i32 ()*) f_rand 
Instruction 0x564adf052070 :  type(void) ptr0x564adf052070  store  type(i32) call4 type(i32*) var4 
Instruction 0x564adf0520f0 :  type(void) ptr0x564adf0520f0  store  type(i32) ptr0x564adf0508f0  type(i32*) var5 
Instruction 0x564adf052170 :  type(void) ptr0x564adf052170  store  type(i32) ptr0x564adf051190  type(i32*) var6 
Instruction 0x564adf0521d8 :  type(i32) ptr0x564adf0521d8  load  type(i32*) var5 
Instruction 0x564adf052238 :  type(i32) ptr0x564adf052238  load  type(i32*) var3 
Instruction 0x564adf04b3e0 :  type(i32) sub  sub  type(i32) ptr0x564adf0521d8  type(i32) ptr0x564adf052238  
Instruction 0x564adf052298 :  type(i32) ptr0x564adf052298  load  type(i32*) var6 
Instruction 0x564adf052310 :  type(i32) mul  mul  type(i32) sub type(i32) ptr0x564adf052298  
Instruction 0x564adf052368 :  type(i32) ptr0x564adf052368  load  type(i32*) var0 
Instruction 0x564adf0523e0 :  type(i32) mul5  mul  type(i32) mul type(i32) ptr0x564adf052368  
Instruction 0x564adf052450 :  type(void) ptr0x564adf052450  store  type(i32) mul5 type(i32*) var2 
Instruction 0x564adf0524b8 :  type(i32) ptr0x564adf0524b8  load  type(i32*) var2 
Instruction 0x564adf052530 :  type(void) ptr0x564adf052530  call  type(i32) ptr0x564adf0524b8  type(void (i32)*) f_printf 
Instruction 0x564adf052598 :  type(i32) ptr0x564adf052598  load  type(i32*) var4 
Instruction 0x564adf0525f8 :  type(i32) ptr0x564adf0525f8  load  type(i32*) p1.addr 
Instruction 0x564adf052670 :  type(i32) mul6  mul  type(i32) ptr0x564adf052598  type(i32) ptr0x564adf0525f8  
Instruction 0x564adf0526e0 :  type(void) ptr0x564adf0526e0  store  type(i32) mul6 type(i32*) var5 
Instruction 0x564adf052748 :  type(i32) ptr0x564adf052748  load  type(i32*) p0.addr 
Instruction 0x564adf0527a8 :  type(i32) ptr0x564adf0527a8  load  type(i32*) var3 
Instruction 0x564adf052820 :  type(i32) mul7  mul  type(i32) ptr0x564adf052748  type(i32) ptr0x564adf0527a8  
Instruction 0x564adf0530a0 :  type(void) ptr0x564adf0530a0  store  type(i32) mul7 type(i32*) var4 
Instruction 0x564adf053108 :  type(i32) ptr0x564adf053108  load  type(i32*) var4 
Instruction 0x564adf053180 :  type(void) ptr0x564adf053180  call  type(i32) ptr0x564adf053108  type(void (i32)*) f_printf 
Instruction 0x564adf0531e8 :  type(i32) ptr0x564adf0531e8  load  type(i32*) var2 
Instruction 0x564adf053248 :  type(i32) ptr0x564adf053248  load  type(i32*) var0 
Instruction 0x564adf0532c0 :  type(i32) sub8  sub  type(i32) ptr0x564adf0531e8  type(i32) ptr0x564adf053248  
Instruction 0x564adf053318 :  type(i32) ptr0x564adf053318  load  type(i32*) var2 
Instruction 0x564adf053390 :  type(i32) sub9  sub  type(i32) sub8 type(i32) ptr0x564adf053318  
Instruction 0x564adf0533e8 :  type(i32) ptr0x564adf0533e8  load  type(i32*) p0.addr 
Instruction 0x564adf053460 :  type(i32) sub10  sub  type(i32) sub9 type(i32) ptr0x564adf0533e8  
Instruction 0x564adf0534d0 :  type(void) ptr0x564adf0534d0  store  type(i32) sub10 type(i32*) p1.addr 
Instruction 0x564adf053538 :  type(i32) ptr0x564adf053538  load  type(i32*) p1.addr 
Instruction 0x564adf0535b0 :  type(void) ptr0x564adf0535b0  call  type(i32) ptr0x564adf053538  type(void (i32)*) f_printf 
Instruction 0x564adf053618 :  type(i32) ptr0x564adf053618  load  type(i32*) var4 
Instruction 0x564adf053678 :  type(i32) ptr0x564adf053678  load  type(i32*) var2 
Instruction 0x564adf0536f0 :  type(i32) mul11  mul  type(i32) ptr0x564adf053618  type(i32) ptr0x564adf053678  
Instruction 0x564adf053760 :  type(void) ptr0x564adf053760  store  type(i32) mul11 type(i32*) var6 
Instruction 0x564adf0537c8 :  type(i32) ptr0x564adf0537c8  load  type(i32*) var6 
Instruction 0x564adf053840 :  type(void) ptr0x564adf053840  call  type(i32) ptr0x564adf0537c8  type(void (i32)*) f_printf 
Instruction 0x564adf0538a8 :  type(i32) ptr0x564adf0538a8  load  type(i32*) var5 
Instruction 0x564adf053908 :  type(i32) ptr0x564adf053908  load  type(i32*) var4 
Instruction 0x564adf053980 :  type(i32) sub12  sub  type(i32) ptr0x564adf0538a8  type(i32) ptr0x564adf053908  
Instruction 0x564adf0539d8 :  type(i32) ptr0x564adf0539d8  load  type(i32*) var3 
Instruction 0x564adf0517d0 :  type(i32) sub13  sub  type(i32) sub12 type(i32) ptr0x564adf0539d8  
Instruction 0x564adf051840 :  type(void) ptr0x564adf051840  store  type(i32) sub13 type(i32*) var6 
Instruction 0x564adf051cb8 :  type(i32) ptr0x564adf051cb8  load  type(i32*) var6 
Instruction 0x564adf051d18 :  type(void) ptr0x564adf051d18  ret  type(i32) ptr0x564adf051cb8  
ENDFunction

Function: func1
BasicBlock: entry
Instruction 0x564adf055838 :  type(i32*) p0.addr  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055898 :  type(i32*) p1.addr  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0558f8 :  type(i32*) var0  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055958 :  type(i32*) var1  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0559b8 :  type(i32*) var2  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055a18 :  type(i32*) var3  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055a78 :  type(i32*) var4  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055ad8 :  type(i32*) var5  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055b38 :  type(i32*) var6  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055bb0 :  type(void) ptr0x564adf055bb0  store  type(i32) p0 type(i32*) p0.addr 
Instruction 0x564adf055c30 :  type(void) ptr0x564adf055c30  store  type(i32) p1 type(i32*) p1.addr 
Instruction 0x564adf055c98 :  type(i32) call  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf055d20 :  type(void) ptr0x564adf055d20  store  type(i32) call type(i32*) var0 
Instruction 0x564adf055d88 :  type(i32) call1  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf055e10 :  type(void) ptr0x564adf055e10  store  type(i32) call1 type(i32*) var1 
Instruction 0x564adf055e78 :  type(i32) call2  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf055f00 :  type(void) ptr0x564adf055f00  store  type(i32) call2 type(i32*) var2 
Instruction 0x564adf055f68 :  type(i32) call3  call  type(i32 ()*) f_rand 
Instruction 0x564adf055ff0 :  type(void) ptr0x564adf055ff0  store  type(i32) call3 type(i32*) var3 
Instruction 0x564adf056058 :  type(i32) call4  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf0560e0 :  type(void) ptr0x564adf0560e0  store  type(i32) call4 type(i32*) var4 
Instruction 0x564adf056160 :  type(void) ptr0x564adf056160  store  type(i32) ptr0x564adf051d60  type(i32*) var5 
Instruction 0x564adf0561e0 :  type(void) ptr0x564adf0561e0  store  type(i32) ptr0x564adf0557f0  type(i32*) var6 
Instruction 0x564adf056248 :  type(i32) ptr0x564adf056248  load  type(i32*) var5 
Instruction 0x564adf0562a8 :  type(i32) ptr0x564adf0562a8  load  type(i32*) p1.addr 
Instruction 0x564adf056320 :  type(i32) sub  sub  type(i32) ptr0x564adf056248  type(i32) ptr0x564adf0562a8  
Instruction 0x564adf056378 :  type(i32) ptr0x564adf056378  load  type(i32*) var6 
Instruction 0x564adf0563f0 :  type(i32) mul  mul  type(i32) sub type(i32) ptr0x564adf056378  
Instruction 0x564adf056448 :  type(i32) ptr0x564adf056448  load  type(i32*) var5 
Instruction 0x564adf0564c0 :  type(i32) mul5  mul  type(i32) mul type(i32) ptr0x564adf056448  
Instruction 0x564adf056518 :  type(i32) ptr0x564adf056518  load  type(i32*) var4 
Instruction 0x564adf056590 :  type(i32) sub6  sub  type(i32) mul5 type(i32) ptr0x564adf056518  
Instruction 0x564adf0565e8 :  type(i32) ptr0x564adf0565e8  load  type(i32*) var0 
Instruction 0x564adf056660 :  type(i32) mul7  mul  type(i32) sub6 type(i32) ptr0x564adf0565e8  
Instruction 0x564adf0566b8 :  type(i32) ptr0x564adf0566b8  load  type(i32*) var4 
Instruction 0x564adf056730 :  type(i32) mul8  mul  type(i32) mul7 type(i32) ptr0x564adf0566b8  
Instruction 0x564adf0567a0 :  type(void) ptr0x564adf0567a0  store  type(i32) mul8 type(i32*) var2 
Instruction 0x564adf056808 :  type(i32) ptr0x564adf056808  load  type(i32*) var4 
Instruction 0x564adf056868 :  type(i32) ptr0x564adf056868  load  type(i32*) p1.addr 
Instruction 0x564adf0568e0 :  type(i32) add  add  type(i32) ptr0x564adf056808  type(i32) ptr0x564adf056868  
Instruction 0x564adf056950 :  type(void) ptr0x564adf056950  store  type(i32) add type(i32*) var1 
Instruction 0x564adf0569b8 :  type(i32) ptr0x564adf0569b8  load  type(i32*) var5 
Instruction 0x564adf056a18 :  type(i32) ptr0x564adf056a18  load  type(i32*) var3 
Instruction 0x564adf056a90 :  type(i32) mul9  mul  type(i32) ptr0x564adf0569b8  type(i32) ptr0x564adf056a18  
Instruction 0x564adf056b00 :  type(void) ptr0x564adf056b00  store  type(i32) mul9 type(i32*) var2 
Instruction 0x564adf056b68 :  type(i32) ptr0x564adf056b68  load  type(i32*) p0.addr 
Instruction 0x564adf056bc8 :  type(i32) ptr0x564adf056bc8  load  type(i32*) var6 
Instruction 0x564adf056c40 :  type(i32) add10  add  type(i32) ptr0x564adf056b68  type(i32) ptr0x564adf056bc8  
Instruction 0x564adf056c98 :  type(i32) ptr0x564adf056c98  load  type(i32*) p0.addr 
Instruction 0x564adf056d10 :  type(i32) sub11  sub  type(i32) add10 type(i32) ptr0x564adf056c98  
Instruction 0x564adf056d68 :  type(i32) ptr0x564adf056d68  load  type(i32*) var3 
Instruction 0x564adf056de0 :  type(i32) mul12  mul  type(i32) sub11 type(i32) ptr0x564adf056d68  
Instruction 0x564adf056e38 :  type(i32) ptr0x564adf056e38  load  type(i32*) var4 
Instruction 0x564adf056eb0 :  type(i32) sub13  sub  type(i32) mul12 type(i32) ptr0x564adf056e38  
Instruction 0x564adf056f20 :  type(void) ptr0x564adf056f20  store  type(i32) sub13 type(i32*) var5 
Instruction 0x564adf056f88 :  type(i32) ptr0x564adf056f88  load  type(i32*) var5 
Instruction 0x564adf057000 :  type(void) ptr0x564adf057000  call  type(i32) ptr0x564adf056f88  type(void (i32)*) f_printf 
Instruction 0x564adf057068 :  type(i32) ptr0x564adf057068  load  type(i32*) p1.addr 
Instruction 0x564adf0570c8 :  type(i32) ptr0x564adf0570c8  load  type(i32*) var0 
Instruction 0x564adf057140 :  type(i32) add14  add  type(i32) ptr0x564adf057068  type(i32) ptr0x564adf0570c8  
Instruction 0x564adf0571b0 :  type(void) ptr0x564adf0571b0  store  type(i32) add14 type(i32*) var5 
Instruction 0x564adf057218 :  type(i32) ptr0x564adf057218  load  type(i32*) var2 
Instruction 0x564adf057278 :  type(i32) ptr0x564adf057278  load  type(i32*) p0.addr 
Instruction 0x564adf0572f0 :  type(i32) add15  add  type(i32) ptr0x564adf057218  type(i32) ptr0x564adf057278  
Instruction 0x564adf057348 :  type(i32) ptr0x564adf057348  load  type(i32*) var2 
Instruction 0x564adf0573c0 :  type(i32) sub16  sub  type(i32) add15 type(i32) ptr0x564adf057348  
Instruction 0x564adf057418 :  type(i32) ptr0x564adf057418  load  type(i32*) var0 
Instruction 0x564adf057490 :  type(i32) sub17  sub  type(i32) sub16 type(i32) ptr0x564adf057418  
Instruction 0x564adf0574e8 :  type(i32) ptr0x564adf0574e8  load  type(i32*) var2 
Instruction 0x564adf057560 :  type(i32) sub18  sub  type(i32) sub17 type(i32) ptr0x564adf0574e8  
Instruction 0x564adf0575b8 :  type(i32) ptr0x564adf0575b8  load  type(i32*) var1 
Instruction 0x564adf057630 :  type(i32) sub19  sub  type(i32) sub18 type(i32) ptr0x564adf0575b8  
Instruction 0x564adf057688 :  type(i32) ptr0x564adf057688  load  type(i32*) var5 
Instruction 0x564adf057700 :  type(i32) sub20  sub  type(i32) sub19 type(i32) ptr0x564adf057688  
Instruction 0x564adf057770 :  type(void) ptr0x564adf057770  store  type(i32) sub20 type(i32*) p0.addr 
Instruction 0x564adf0577d8 :  type(i32) ptr0x564adf0577d8  load  type(i32*) p0.addr 
Instruction 0x564adf057838 :  type(void) ptr0x564adf057838  ret  type(i32) ptr0x564adf0577d8  
ENDFunction

Function: func2
BasicBlock: entry
Instruction 0x564adf058368 :  type(i32*) var0  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0583c8 :  type(i32*) var1  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf058428 :  type(i32*) var2  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf058488 :  type(i32*) var3  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0584e8 :  type(i32*) var4  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf058548 :  type(i32*) var5  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0585a8 :  type(i32*) var6  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf058608 :  type(i32) call  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf058690 :  type(void) ptr0x564adf058690  store  type(i32) call type(i32*) var0 
Instruction 0x564adf0586f8 :  type(i32) call1  call  type(i32 ()*) f_rand 
Instruction 0x564adf058780 :  type(void) ptr0x564adf058780  store  type(i32) call1 type(i32*) var1 
Instruction 0x564adf0587e8 :  type(i32) call2  call  type(i32 ()*) f_rand 
Instruction 0x564adf058870 :  type(void) ptr0x564adf058870  store  type(i32) call2 type(i32*) var2 
Instruction 0x564adf0588d8 :  type(i32) call3  call  type(i32 ()*) f_rand 
Instruction 0x564adf058960 :  type(void) ptr0x564adf058960  store  type(i32) call3 type(i32*) var3 
Instruction 0x564adf0589c8 :  type(i32) call4  call  type(i32 ()*) f_rand 
Instruction 0x564adf058a50 :  type(void) ptr0x564adf058a50  store  type(i32) call4 type(i32*) var4 
Instruction 0x564adf058ad0 :  type(void) ptr0x564adf058ad0  store  type(i32) ptr0x564adf057880  type(i32*) var5 
Instruction 0x564adf058b50 :  type(void) ptr0x564adf058b50  store  type(i32) ptr0x564adf058320  type(i32*) var6 
Instruction 0x564adf058bb8 :  type(i32) ptr0x564adf058bb8  load  type(i32*) var6 
Instruction 0x564adf058c18 :  type(i32) ptr0x564adf058c18  load  type(i32*) var1 
Instruction 0x564adf058c90 :  type(i32) sub  sub  type(i32) ptr0x564adf058bb8  type(i32) ptr0x564adf058c18  
Instruction 0x564adf058d00 :  type(void) ptr0x564adf058d00  store  type(i32) sub type(i32*) var3 
Instruction 0x564adf058d68 :  type(i32) ptr0x564adf058d68  load  type(i32*) var3 
Instruction 0x564adf058de0 :  type(void) ptr0x564adf058de0  call  type(i32) ptr0x564adf058d68  type(void (i32)*) f_printf 
Instruction 0x564adf058e48 :  type(i32) ptr0x564adf058e48  load  type(i32*) var6 
Instruction 0x564adf058ea8 :  type(i32) ptr0x564adf058ea8  load  type(i32*) var5 
Instruction 0x564adf058f20 :  type(i32) add  add  type(i32) ptr0x564adf058e48  type(i32) ptr0x564adf058ea8  
Instruction 0x564adf058f90 :  type(void) ptr0x564adf058f90  store  type(i32) add type(i32*) var5 
Instruction 0x564adf058ff8 :  type(i32) ptr0x564adf058ff8  load  type(i32*) var5 
Instruction 0x564adf059070 :  type(void) ptr0x564adf059070  call  type(i32) ptr0x564adf058ff8  type(void (i32)*) f_printf 
Instruction 0x564adf0590d8 :  type(i32) ptr0x564adf0590d8  load  type(i32*) var2 
Instruction 0x564adf059138 :  type(i32) ptr0x564adf059138  load  type(i32*) var3 
Instruction 0x564adf0591b0 :  type(i32) mul  mul  type(i32) ptr0x564adf0590d8  type(i32) ptr0x564adf059138  
Instruction 0x564adf059220 :  type(void) ptr0x564adf059220  store  type(i32) mul type(i32*) var6 
Instruction 0x564adf059288 :  type(i32) ptr0x564adf059288  load  type(i32*) var6 
Instruction 0x564adf0592e8 :  type(i32) ptr0x564adf0592e8  load  type(i32*) var2 
Instruction 0x564adf059360 :  type(i32) mul5  mul  type(i32) ptr0x564adf059288  type(i32) ptr0x564adf0592e8  
Instruction 0x564adf0593b8 :  type(i32) ptr0x564adf0593b8  load  type(i32*) var0 
Instruction 0x564adf059430 :  type(i32) sub6  sub  type(i32) mul5 type(i32) ptr0x564adf0593b8  
Instruction 0x564adf0594a0 :  type(void) ptr0x564adf0594a0  store  type(i32) sub6 type(i32*) var0 
Instruction 0x564adf059508 :  type(i32) ptr0x564adf059508  load  type(i32*) var0 
Instruction 0x564adf059580 :  type(void) ptr0x564adf059580  call  type(i32) ptr0x564adf059508  type(void (i32)*) f_printf 
Instruction 0x564adf0595e8 :  type(i32) ptr0x564adf0595e8  load  type(i32*) var5 
Instruction 0x564adf059648 :  type(i32) ptr0x564adf059648  load  type(i32*) var3 
Instruction 0x564adf0596c0 :  type(i32) add7  add  type(i32) ptr0x564adf0595e8  type(i32) ptr0x564adf059648  
Instruction 0x564adf059718 :  type(i32) ptr0x564adf059718  load  type(i32*) var2 
Instruction 0x564adf059790 :  type(i32) sub8  sub  type(i32) add7 type(i32) ptr0x564adf059718  
Instruction 0x564adf0597e8 :  type(i32) ptr0x564adf0597e8  load  type(i32*) var6 
Instruction 0x564adf059860 :  type(i32) mul9  mul  type(i32) sub8 type(i32) ptr0x564adf0597e8  
Instruction 0x564adf0598b8 :  type(i32) ptr0x564adf0598b8  load  type(i32*) var2 
Instruction 0x564adf059930 :  type(i32) add10  add  type(i32) mul9 type(i32) ptr0x564adf0598b8  
Instruction 0x564adf0599a0 :  type(void) ptr0x564adf0599a0  store  type(i32) add10 type(i32*) var2 
Instruction 0x564adf059a08 :  type(i32) ptr0x564adf059a08  load  type(i32*) var2 
Instruction 0x564adf059a80 :  type(void) ptr0x564adf059a80  call  type(i32) ptr0x564adf059a08  type(void (i32)*) f_printf 
Instruction 0x564adf059ae8 :  type(i32) ptr0x564adf059ae8  load  type(i32*) var1 
Instruction 0x564adf059b48 :  type(i32) ptr0x564adf059b48  load  type(i32*) var5 
Instruction 0x564adf059bc0 :  type(i32) mul11  mul  type(i32) ptr0x564adf059ae8  type(i32) ptr0x564adf059b48  
Instruction 0x564adf059c30 :  type(void) ptr0x564adf059c30  store  type(i32) mul11 type(i32*) var2 
Instruction 0x564adf059c98 :  type(i32) ptr0x564adf059c98  load  type(i32*) var2 
Instruction 0x564adf059cf8 :  type(void) ptr0x564adf059cf8  ret  type(i32) ptr0x564adf059c98  
ENDFunction

Function: func3
BasicBlock: entry
Instruction 0x564adf0552c8 :  type(i32*) var0  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055328 :  type(i32*) var1  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055388 :  type(i32*) var2  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0553e8 :  type(i32*) var3  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055448 :  type(i32*) var4  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf0554a8 :  type(i32*) var5  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055508 :  type(i32*) var6  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf055568 :  type(i32) call  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf0555f0 :  type(void) ptr0x564adf0555f0  store  type(i32) call type(i32*) var0 
Instruction 0x564adf055658 :  type(i32) call1  call  type(i32 ()*) f_rand 
Instruction 0x564adf05afb0 :  type(void) ptr0x564adf05afb0  store  type(i32) call1 type(i32*) var1 
Instruction 0x564adf05b018 :  type(i32) call2  call  type(i32 ()*) f_rand 
Instruction 0x564adf05b0a0 :  type(void) ptr0x564adf05b0a0  store  type(i32) call2 type(i32*) var2 
Instruction 0x564adf05b108 :  type(i32) call3  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf05b190 :  type(void) ptr0x564adf05b190  store  type(i32) call3 type(i32*) var3 
Instruction 0x564adf05b1f8 :  type(i32) call4  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf05b280 :  type(void) ptr0x564adf05b280  store  type(i32) call4 type(i32*) var4 
Instruction 0x564adf05b300 :  type(void) ptr0x564adf05b300  store  type(i32) ptr0x564adf059d40  type(i32*) var5 
Instruction 0x564adf05b380 :  type(void) ptr0x564adf05b380  store  type(i32) ptr0x564adf055280  type(i32*) var6 
Instruction 0x564adf05b3e8 :  type(i32) ptr0x564adf05b3e8  load  type(i32*) var0 
Instruction 0x564adf05b448 :  type(i32) ptr0x564adf05b448  load  type(i32*) var3 
Instruction 0x564adf05b4c0 :  type(i32) add  add  type(i32) ptr0x564adf05b3e8  type(i32) ptr0x564adf05b448  
Instruction 0x564adf05b530 :  type(void) ptr0x564adf05b530  store  type(i32) add type(i32*) var6 
Instruction 0x564adf05b598 :  type(i32) ptr0x564adf05b598  load  type(i32*) var6 
Instruction 0x564adf05b610 :  type(void) ptr0x564adf05b610  call  type(i32) ptr0x564adf05b598  type(void (i32)*) f_printf 
Instruction 0x564adf05b678 :  type(i32) ptr0x564adf05b678  load  type(i32*) var1 
Instruction 0x564adf05b6d8 :  type(i32) ptr0x564adf05b6d8  load  type(i32*) var6 
Instruction 0x564adf05b750 :  type(i32) add5  add  type(i32) ptr0x564adf05b678  type(i32) ptr0x564adf05b6d8  
Instruction 0x564adf05b7a8 :  type(i32) ptr0x564adf05b7a8  load  type(i32*) var4 
Instruction 0x564adf052890 :  type(i32) sub  sub  type(i32) add5 type(i32) ptr0x564adf05b7a8  
Instruction 0x564adf0528e8 :  type(i32) ptr0x564adf0528e8  load  type(i32*) var2 
Instruction 0x564adf052960 :  type(i32) sub6  sub  type(i32) sub type(i32) ptr0x564adf0528e8  
Instruction 0x564adf0529d0 :  type(void) ptr0x564adf0529d0  store  type(i32) sub6 type(i32*) var6 
Instruction 0x564adf052a38 :  type(i32) ptr0x564adf052a38  load  type(i32*) var3 
Instruction 0x564adf052a98 :  type(i32) ptr0x564adf052a98  load  type(i32*) var5 
Instruction 0x564adf052b10 :  type(i32) mul  mul  type(i32) ptr0x564adf052a38  type(i32) ptr0x564adf052a98  
Instruction 0x564adf052b80 :  type(void) ptr0x564adf052b80  store  type(i32) mul type(i32*) var3 
Instruction 0x564adf052be8 :  type(i32) ptr0x564adf052be8  load  type(i32*) var3 
Instruction 0x564adf052c60 :  type(void) ptr0x564adf052c60  call  type(i32) ptr0x564adf052be8  type(void (i32)*) f_printf 
Instruction 0x564adf052cc8 :  type(i32) ptr0x564adf052cc8  load  type(i32*) var2 
Instruction 0x564adf052d28 :  type(i32) ptr0x564adf052d28  load  type(i32*) var5 
Instruction 0x564adf052da0 :  type(i32) add7  add  type(i32) ptr0x564adf052cc8  type(i32) ptr0x564adf052d28  
Instruction 0x564adf052e10 :  type(void) ptr0x564adf052e10  store  type(i32) add7 type(i32*) var5 
Instruction 0x564adf052e78 :  type(i32) ptr0x564adf052e78  load  type(i32*) var5 
Instruction 0x564adf052ef0 :  type(void) ptr0x564adf052ef0  call  type(i32) ptr0x564adf052e78  type(void (i32)*) f_printf 
Instruction 0x564adf052f58 :  type(i32) ptr0x564adf052f58  load  type(i32*) var0 
Instruction 0x564adf052fb8 :  type(i32) ptr0x564adf052fb8  load  type(i32*) var2 
Instruction 0x564adf053030 :  type(i32) sub8  sub  type(i32) ptr0x564adf052f58  type(i32) ptr0x564adf052fb8  
Instruction 0x564adf05c030 :  type(void) ptr0x564adf05c030  store  type(i32) sub8 type(i32*) var6 
Instruction 0x564adf05c098 :  type(i32) ptr0x564adf05c098  load  type(i32*) var6 
Instruction 0x564adf05c110 :  type(void) ptr0x564adf05c110  call  type(i32) ptr0x564adf05c098  type(void (i32)*) f_printf 
Instruction 0x564adf05c178 :  type(i32) ptr0x564adf05c178  load  type(i32*) var0 
Instruction 0x564adf05c1d8 :  type(i32) ptr0x564adf05c1d8  load  type(i32*) var2 
Instruction 0x564adf05c250 :  type(i32) add9  add  type(i32) ptr0x564adf05c178  type(i32) ptr0x564adf05c1d8  
Instruction 0x564adf05c2a8 :  type(i32) ptr0x564adf05c2a8  load  type(i32*) var5 
Instruction 0x564adf05c320 :  type(i32) mul10  mul  type(i32) add9 type(i32) ptr0x564adf05c2a8  
Instruction 0x564adf05c390 :  type(void) ptr0x564adf05c390  store  type(i32) mul10 type(i32*) var6 
Instruction 0x564adf05c3f8 :  type(i32) ptr0x564adf05c3f8  load  type(i32*) var6 
Instruction 0x564adf05c458 :  type(void) ptr0x564adf05c458  ret  type(i32) ptr0x564adf05c3f8  
ENDFunction

Function: func4
BasicBlock: entry
Instruction 0x564adf05caf8 :  type(i32*) p0.addr  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05cb58 :  type(i32*) p1.addr  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05cbb8 :  type(i32*) p2.addr  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05cc18 :  type(i32*) var0  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05cc78 :  type(i32*) var1  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05ccd8 :  type(i32*) var2  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05cd38 :  type(i32*) var3  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05cd98 :  type(i32*) var4  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05cdf8 :  type(i32*) var5  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05ce58 :  type(i32*) var6  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05ced0 :  type(void) ptr0x564adf05ced0  store  type(i32) p0 type(i32*) p0.addr 
Instruction 0x564adf05cf50 :  type(void) ptr0x564adf05cf50  store  type(i32) p1 type(i32*) p1.addr 
Instruction 0x564adf05cfd0 :  type(void) ptr0x564adf05cfd0  store  type(i32) p2 type(i32*) p2.addr 
Instruction 0x564adf05d038 :  type(i32) call  call  type(i32 ()*) f_rand 
Instruction 0x564adf05d0c0 :  type(void) ptr0x564adf05d0c0  store  type(i32) call type(i32*) var0 
Instruction 0x564adf05d128 :  type(i32) call1  call  type(i32 ()*) f_rand 
Instruction 0x564adf05d1b0 :  type(void) ptr0x564adf05d1b0  store  type(i32) call1 type(i32*) var1 
Instruction 0x564adf05d218 :  type(i32) call2  call  type(i32 ()*) f_rand 
Instruction 0x564adf05d2a0 :  type(void) ptr0x564adf05d2a0  store  type(i32) call2 type(i32*) var2 
Instruction 0x564adf05d308 :  type(i32) call3  call  type(i32 ()*) f_rand 
Instruction 0x564adf05d390 :  type(void) ptr0x564adf05d390  store  type(i32) call3 type(i32*) var3 
Instruction 0x564adf05d3f8 :  type(i32) call4  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf05d480 :  type(void) ptr0x564adf05d480  store  type(i32) call4 type(i32*) var4 
Instruction 0x564adf05d500 :  type(void) ptr0x564adf05d500  store  type(i32) ptr0x564adf0556b0  type(i32*) var5 
Instruction 0x564adf05d580 :  type(void) ptr0x564adf05d580  store  type(i32) ptr0x564adf05cab0  type(i32*) var6 
Instruction 0x564adf05d5e8 :  type(i32) ptr0x564adf05d5e8  load  type(i32*) p2.addr 
Instruction 0x564adf05d648 :  type(i32) ptr0x564adf05d648  load  type(i32*) var1 
Instruction 0x564adf05d6c0 :  type(i32) sub  sub  type(i32) ptr0x564adf05d5e8  type(i32) ptr0x564adf05d648  
Instruction 0x564adf05d718 :  type(i32) ptr0x564adf05d718  load  type(i32*) var5 
Instruction 0x564adf05d790 :  type(i32) mul  mul  type(i32) sub type(i32) ptr0x564adf05d718  
Instruction 0x564adf05d800 :  type(void) ptr0x564adf05d800  store  type(i32) mul type(i32*) p2.addr 
Instruction 0x564adf05d868 :  type(i32) ptr0x564adf05d868  load  type(i32*) p0.addr 
Instruction 0x564adf05d8c8 :  type(i32) ptr0x564adf05d8c8  load  type(i32*) var2 
Instruction 0x564adf05d940 :  type(i32) mul5  mul  type(i32) ptr0x564adf05d868  type(i32) ptr0x564adf05d8c8  
Instruction 0x564adf05d9b0 :  type(void) ptr0x564adf05d9b0  store  type(i32) mul5 type(i32*) var1 
Instruction 0x564adf05da18 :  type(i32) ptr0x564adf05da18  load  type(i32*) var1 
Instruction 0x564adf05da78 :  type(i32) ptr0x564adf05da78  load  type(i32*) p0.addr 
Instruction 0x564adf05daf0 :  type(i32) mul6  mul  type(i32) ptr0x564adf05da18  type(i32) ptr0x564adf05da78  
Instruction 0x564adf05db48 :  type(i32) ptr0x564adf05db48  load  type(i32*) var3 
Instruction 0x564adf05dbc0 :  type(i32) mul7  mul  type(i32) mul6 type(i32) ptr0x564adf05db48  
Instruction 0x564adf05dc18 :  type(i32) ptr0x564adf05dc18  load  type(i32*) p1.addr 
Instruction 0x564adf05dc90 :  type(i32) mul8  mul  type(i32) mul7 type(i32) ptr0x564adf05dc18  
Instruction 0x564adf05dd00 :  type(void) ptr0x564adf05dd00  store  type(i32) mul8 type(i32*) var5 
Instruction 0x564adf05dd68 :  type(i32) ptr0x564adf05dd68  load  type(i32*) p2.addr 
Instruction 0x564adf05ddc8 :  type(i32) ptr0x564adf05ddc8  load  type(i32*) var3 
Instruction 0x564adf05de40 :  type(i32) add  add  type(i32) ptr0x564adf05dd68  type(i32) ptr0x564adf05ddc8  
Instruction 0x564adf05de98 :  type(i32) ptr0x564adf05de98  load  type(i32*) var1 
Instruction 0x564adf05df10 :  type(i32) mul9  mul  type(i32) add type(i32) ptr0x564adf05de98  
Instruction 0x564adf05df68 :  type(i32) ptr0x564adf05df68  load  type(i32*) var3 
Instruction 0x564adf05dfe0 :  type(i32) mul10  mul  type(i32) mul9 type(i32) ptr0x564adf05df68  
Instruction 0x564adf05e050 :  type(void) ptr0x564adf05e050  store  type(i32) mul10 type(i32*) p2.addr 
Instruction 0x564adf05e0b8 :  type(i32) ptr0x564adf05e0b8  load  type(i32*) p2.addr 
Instruction 0x564adf05e130 :  type(void) ptr0x564adf05e130  call  type(i32) ptr0x564adf05e0b8  type(void (i32)*) f_printf 
Instruction 0x564adf05e198 :  type(i32) ptr0x564adf05e198  load  type(i32*) var3 
Instruction 0x564adf05e1f8 :  type(i32) ptr0x564adf05e1f8  load  type(i32*) var6 
Instruction 0x564adf05e270 :  type(i32) add11  add  type(i32) ptr0x564adf05e198  type(i32) ptr0x564adf05e1f8  
Instruction 0x564adf05e2c8 :  type(i32) ptr0x564adf05e2c8  load  type(i32*) p2.addr 
Instruction 0x564adf05e340 :  type(i32) sub12  sub  type(i32) add11 type(i32) ptr0x564adf05e2c8  
Instruction 0x564adf05e398 :  type(i32) ptr0x564adf05e398  load  type(i32*) var5 
Instruction 0x564adf05e410 :  type(i32) sub13  sub  type(i32) sub12 type(i32) ptr0x564adf05e398  
Instruction 0x564adf05e480 :  type(void) ptr0x564adf05e480  store  type(i32) sub13 type(i32*) var3 
Instruction 0x564adf05e4e8 :  type(i32) ptr0x564adf05e4e8  load  type(i32*) var0 
Instruction 0x564adf05e548 :  type(i32) ptr0x564adf05e548  load  type(i32*) var5 
Instruction 0x564adf05e5c0 :  type(i32) mul14  mul  type(i32) ptr0x564adf05e4e8  type(i32) ptr0x564adf05e548  
Instruction 0x564adf05e630 :  type(void) ptr0x564adf05e630  store  type(i32) mul14 type(i32*) var3 
Instruction 0x564adf05e698 :  type(i32) ptr0x564adf05e698  load  type(i32*) var3 
Instruction 0x564adf05e6f8 :  type(void) ptr0x564adf05e6f8  ret  type(i32) ptr0x564adf05e698  
ENDFunction

Function: main
BasicBlock: entry
Instruction 0x564adf05f098 :  type(i32*) retval  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05f0f8 :  type(i32*) var0  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05f158 :  type(i32*) var1  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05f1b8 :  type(i32*) var2  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05f218 :  type(i32*) var3  alloca  type(i32) ptr0x564adf04d1e0  
Instruction 0x564adf05f290 :  type(void) ptr0x564adf05f290  store  type(i32) ptr0x564adf05e740  type(i32*) retval 
Instruction 0x564adf05f2f8 :  type(i32) call  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf05f380 :  type(void) ptr0x564adf05f380  store  type(i32) call type(i32*) var0 
Instruction 0x564adf05f3e8 :  type(i32) call1  call  type(i32 ()*) f_rand 
Instruction 0x564adf05f470 :  type(void) ptr0x564adf05f470  store  type(i32) call1 type(i32*) var1 
Instruction 0x564adf05f4d8 :  type(i32) call2  call  type(i32 ()*) f_rand 
Instruction 0x564adf05f560 :  type(void) ptr0x564adf05f560  store  type(i32) call2 type(i32*) var2 
Instruction 0x564adf05f5c8 :  type(i32) call3  call  type(i32 ()*) f_scanf_nop 
Instruction 0x564adf05f650 :  type(void) ptr0x564adf05f650  store  type(i32) call3 type(i32*) var3 
Instruction 0x564adf05f6b8 :  type(i32) ptr0x564adf05f6b8  load  type(i32*) var0 
Instruction 0x564adf05f718 :  type(i32) ptr0x564adf05f718  load  type(i32*) var1 
Instruction 0x564adf05f7a8 :  type(i32) call4  call  type(i32) ptr0x564adf05f6b8  type(i32) ptr0x564adf05f718  type(i32 (i32, i32)*) func0 
Instruction 0x564adf05f818 :  type(i32) ptr0x564adf05f818  load  type(i32*) var0 
Instruction 0x564adf05f878 :  type(i32) ptr0x564adf05f878  load  type(i32*) var1 
Instruction 0x564adf05f908 :  type(i32) call5  call  type(i32) ptr0x564adf05f818  type(i32) ptr0x564adf05f878  type(i32 (i32, i32)*) func1 
Instruction 0x564adf05f978 :  type(i32) call6  call  type(i32 ()*) func2 
Instruction 0x564adf05f9e8 :  type(i32) call7  call  type(i32 ()*) func3 
Instruction 0x564adf05fa58 :  type(i32) ptr0x564adf05fa58  load  type(i32*) var0 
Instruction 0x564adf05fab8 :  type(i32) ptr0x564adf05fab8  load  type(i32*) var1 
Instruction 0x564adf05fb18 :  type(i32) ptr0x564adf05fb18  load  type(i32*) var2 
Instruction 0x564adf05fbc0 :  type(i32) call8  call  type(i32) ptr0x564adf05fa58  type(i32) ptr0x564adf05fab8  type(i32) ptr0x564adf05fb18  type(i32 (i32, i32, i32)*) func4 
Instruction 0x564adf05fc28 :  type(void) ptr0x564adf05fc28  ret  type(i32) ptr0x564adf05e740  
ENDFunction

