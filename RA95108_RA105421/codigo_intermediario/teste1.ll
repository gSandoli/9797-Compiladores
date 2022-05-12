; ModuleID = 'main'
source_filename = "main"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

define void @main() {
entry:
  %x = alloca i64, align 8
  %t2 = alloca i64, align 8
  %t1 = alloca i64, align 8
  %i = alloca i64, align 8
  %n = alloca i64, align 8
  store i64 0, i64* %n, align 8
  store i64 3, i64* %i, align 8
  store i64 0, i64* %t1, align 8
  store i64 1, i64* %t2, align 8
  store i64 1, i64* %x, align 8
  %0 = call i64 @li()
  store i64 %0, i64* %n, align 8
  %t11 = load i64, i64* %t1, align 8
  %t22 = load i64, i64* %t2, align 8
  %addtmp = add i64 %t11, %t22
  store i64 %addtmp, i64* %x, align 8
  %t13 = load i64, i64* %t1, align 8
  call void @imprimei(i64 %t13)
  %t24 = load i64, i64* %t2, align 8
  call void @imprimei(i64 %t24)
  br label %test

test:                                             ; preds = %next, %entry
  %i5 = load i64, i64* %i, align 8
  %n6 = load i64, i64* %n, align 8
  %cmptmp = icmp sle i64 %i5, %n6
  %cmptmp7 = zext i1 %cmptmp to i64
  %loopcond = icmp eq i64 %cmptmp7, 0
  br i1 %loopcond, label %after, label %loop

loop:                                             ; preds = %test
  %x8 = load i64, i64* %x, align 8
  call void @imprimei(i64 %x8)
  %t29 = load i64, i64* %t2, align 8
  store i64 %t29, i64* %t1, align 8
  %x10 = load i64, i64* %x, align 8
  store i64 %x10, i64* %t2, align 8
  %t111 = load i64, i64* %t1, align 8
  %t212 = load i64, i64* %t2, align 8
  %addtmp13 = add i64 %t111, %t212
  store i64 %addtmp13, i64* %x, align 8
  %i14 = load i64, i64* %i, align 8
  %addtmp15 = add i64 %i14, 1
  store i64 %addtmp15, i64* %i, align 8
  br label %next

next:                                             ; preds = %loop
  br label %test

after:                                            ; preds = %test
  %x16 = load i64, i64* %x, align 8
  call void @imprimei(i64 %x16)
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
