; ModuleID = 'main'
source_filename = "main"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

define void @main() {
entry:
  %r = alloca i64, align 8
  %i = alloca i64, align 8
  %e = alloca i64, align 8
  %b = alloca i64, align 8
  store i64 0, i64* %b, align 8
  store i64 0, i64* %e, align 8
  store i64 0, i64* %i, align 8
  store i64 1, i64* %r, align 8
  %0 = call i64 @li()
  store i64 %0, i64* %b, align 8
  %1 = call i64 @li()
  store i64 %1, i64* %e, align 8
  br label %test

test:                                             ; preds = %next, %entry
  %i1 = load i64, i64* %i, align 8
  %e2 = load i64, i64* %e, align 8
  %cmptmp = icmp slt i64 %i1, %e2
  %cmptmp3 = zext i1 %cmptmp to i64
  %loopcond = icmp eq i64 %cmptmp3, 0
  br i1 %loopcond, label %after, label %loop

loop:                                             ; preds = %test
  %r4 = load i64, i64* %r, align 8
  %b5 = load i64, i64* %b, align 8
  %multmp = mul i64 %r4, %b5
  store i64 %multmp, i64* %r, align 8
  %i6 = load i64, i64* %i, align 8
  %addtmp = add i64 %i6, 1
  store i64 %addtmp, i64* %i, align 8
  br label %next

next:                                             ; preds = %loop
  br label %test

after:                                            ; preds = %test
  %r7 = load i64, i64* %r, align 8
  call void @imprimei(i64 %r7)
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
