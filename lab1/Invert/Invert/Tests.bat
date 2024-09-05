@echo off

SET PROGRAM="%~1"

REM Тест при недостатке аргументов
echo Test 1.1
%PROGRAM% > nul && goto err

REM Тест при избыточном количестве аргументов
echo Test 1.2
%PROGRAM% "matrix.txt" "long" > nul && goto err

REM Тест с обычной матрицей
echo Test 2
%PROGRAM% "matrix.txt" || goto err

REM Тест матрицы с определителем = 0
echo Test 3
%PROGRAM% "matrix1.txt" || goto 

REM Тест матрицы с недостающим количестов элементов
echo Test 4
%PROGRAM% "matrix2.txt" && goto err

REM Тест матрицы с некорректными элементами
echo Test 5
%PROGRAM% "matrix3.txt" && goto err

echo Success!
exit 0

:err
echo Program failed
exit 1