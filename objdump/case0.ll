; ModuleID = 'case0.bc'
source_filename = "case0.c"
target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
target triple = "aarch64"

@c = dso_local local_unnamed_addr global i32 0, align 4
@i = dso_local local_unnamed_addr global i32 1, align 4
@j = dso_local local_unnamed_addr global i32 0, align 4
@a = dso_local local_unnamed_addr global [30 x i32] zeroinitializer, align 4
@b = dso_local local_unnamed_addr global [30 x i32] zeroinitializer, align 4
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nofree nounwind
define dso_local i32 @main() local_unnamed_addr #0 {
  %1 = load i32, i32* @i, align 4, !tbaa !2
  %2 = icmp slt i32 %1, 32
  br i1 %2, label %3, label %36

3:                                                ; preds = %0
  %4 = load i32, i32* @c, align 4
  br label %5

5:                                                ; preds = %3, %32
  %6 = phi i32 [ %34, %32 ], [ %4, %3 ]
  %7 = phi i32 [ %33, %32 ], [ %1, %3 ]
  %8 = icmp eq i32 %6, 15
  %9 = icmp eq i32 %7, 31
  br i1 %9, label %10, label %11

10:                                               ; preds = %18, %5
  store i32 1, i32* @i, align 4, !tbaa !2
  br label %32

11:                                               ; preds = %5, %18
  %12 = phi i32 [ %19, %18 ], [ %7, %5 ]
  br i1 %8, label %36, label %13

13:                                               ; preds = %11
  %14 = sext i32 %12 to i64
  %15 = getelementptr inbounds [30 x i32], [30 x i32]* @b, i64 0, i64 %14
  %16 = load i32, i32* %15, align 4, !tbaa !2
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %21, label %18

18:                                               ; preds = %21, %13
  %19 = add nsw i32 %12, 1
  store i32 %19, i32* @i, align 4, !tbaa !2
  %20 = icmp eq i32 %19, 31
  br i1 %20, label %10, label %11

21:                                               ; preds = %13
  %22 = load i32, i32* @j, align 4, !tbaa !2
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* @j, align 4, !tbaa !2
  %24 = icmp eq i32 %23, 9
  br i1 %24, label %25, label %18

25:                                               ; preds = %21
  store i32 1, i32* %15, align 4, !tbaa !2
  %26 = getelementptr inbounds [30 x i32], [30 x i32]* @a, i64 0, i64 %14
  store i32 9, i32* %26, align 4, !tbaa !2
  store i32 0, i32* @j, align 4, !tbaa !2
  %27 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %12)
  %28 = load i32, i32* @i, align 4, !tbaa !2
  %29 = add nsw i32 %28, 1
  store i32 %29, i32* @i, align 4, !tbaa !2
  %30 = load i32, i32* @c, align 4, !tbaa !2
  %31 = add nsw i32 %30, 1
  store i32 %31, i32* @c, align 4, !tbaa !2
  br label %32

32:                                               ; preds = %25, %10
  %33 = phi i32 [ %29, %25 ], [ 1, %10 ]
  %34 = phi i32 [ %31, %25 ], [ %6, %10 ]
  %35 = icmp slt i32 %33, 32
  br i1 %35, label %5, label %36

36:                                               ; preds = %32, %11, %0
  ret i32 0
}

; Function Attrs: nofree nounwind
declare dso_local i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #1

attributes #0 = { nofree nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nofree nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
!2 = !{!3, !3, i64 0}
!3 = !{!"int", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C/C++ TBAA"}
