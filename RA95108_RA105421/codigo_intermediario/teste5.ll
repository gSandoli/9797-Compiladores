; ModuleID = 'main'
source_filename = "main"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

define void @main() {
entry:
  %r = alloca i64, align 8
  %i = alloca i64, align 8
  %n = alloca i64, align 8
  store i64 0, i64* %n, align 8
  store i64 0, i64* %i, align 8
  store i64 1, i64* %r, align 8
  %0 = call i64 @li()
  store i64 %0, i64* %n, align 8
  %n1 = load i64, i64* %n, align 8
  %cmptmp = icmp eq i64 %n1, 0
  %cmptmp2 = zext i1 %cmptmp to i64
  %n3 = load i64, i64* %n, align 8
  %cmptmp4 = icmp eq i64 %n3, 1
  %cmptmp5 = zext i1 %cmptmp4 to i64
  %andtmp = or i64 %cmptmp2, %cmptmp5
  %ifcast = trunc i64 %andtmp to i1
  %iftest = icmp ne i1 %ifcast, true
  br i1 %ifcast, label %then, label %ifcont

then:                                             ; preds = %entry
  %n6 = load i64, i64* %n, align 8
  call void @imprimei(i64 %n6)
  call void @termine(i64 0)
  br label %ifcont

ifcont:                                           ; preds = %then, %entry
  br label %test

test:                                             ; preds = %next, %ifcont
  %r7 = load i64, i64* %r, align 8
  %n8 = load i64, i64* %n, align 8
  %cmptmp9 = icmp sle i64 %r7, %n8
  %cmptmp10 = zext i1 %cmptmp9 to i64
  %loopcond = icmp eq i64 %cmptmp10, 0
  br i1 %loopcond, label %after, label %loop

loop:                                             ; preds = %test
  %i11 = load i64, i64* %i, align 8
  %addtmp = add i64 %i11, 1
  store i64 %addtmp, i64* %i, align 8
  %i12 = load i64, i64* %i, align 8
  %i13 = load i64, i64* %i, align 8
  %multmp = mul i64 %i12, %i13
  store i64 %multmp, i64* %r, align 8
  br label %next

next:                                             ; preds = %loop
  br label %test

after:                                            ; preds = %test
  %i14 = load i64, i64* %i, align 8
  %subtmp = sub i64 %i14, 1
  call void @imprimei(i64 %subtmp)
  call void @termine(i64 0)
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
