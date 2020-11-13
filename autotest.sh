> compare.txt ; > compare1.txt
./minishell < test.sh > compare.txt
bash < test.sh > compare1.txt 
diff -y -W 120 --suppress-common-lines --color compare.txt compare1.txt
rm compare1.txt compare.txt
