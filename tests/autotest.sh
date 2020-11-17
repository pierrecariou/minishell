cd ..
make
./minishell < tests/test.sh > tests/compare.txt
bash < tests/test.sh > tests/compare1.txt 
diff -y -W 120 --suppress-common-lines --color tests/compare.txt tests/compare1.txt
rm tests/compare1.txt tests/compare.txt
