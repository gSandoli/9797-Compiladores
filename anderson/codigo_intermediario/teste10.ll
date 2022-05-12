; ModuleID = 'main'
source_filename = "main"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

define void @main() {
entry:
  %g2 = alloca i64, align 8
  %g1 = alloca i64, align 8
  store i64 10, i64* %g1, align 8
  store i64 20, i64* %g2, align 8
  %g11 = load i64, i64* %g1, align 8
  %cmptmp = icmp sgt i64 %g11, 15
  %cmptmp2 = zext i1 %cmptmp to i64
  %g23 = load i64, i64* %g2, align 8
  %cmptmp4 = icmp slt i64 %g23, 30
  %cmptmp5 = zext i1 %cmptmp4 to i64
  %andtmp = or i64 %cmptmp2, %cmptmp5
  %ifcast = trunc i64 %andtmp to i1
  %iftest = icmp ne i1 %ifcast, true
  br i1 %ifcast, label %then, label %else

then:                                             ; preds = %entry
  call void @imprimei(i64 1)
  br label %ifcont

else:                                             ; preds = %entry
  call void @imprimei(i64 0)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret void
}

declare void @imprimei(i64)

declare void @imprimer(double)

declare void @imprimec(i8*)

declare void @emite()

declare i8* @lc()

declare i64 @li()

declare double @lr()

declare i64 @ordem(i8*)

declare i8* @chr(i64)

declare i64 @tamanho(i8*)

declare i8* @subcadeia(i8*, i64, i64)

declare i8* @concatene(i8*, i8*)

declare i64 @inverter(i64)

declare void @termine(i64)

declare i64 @gere_inteiro()

declare double @gere_real()
