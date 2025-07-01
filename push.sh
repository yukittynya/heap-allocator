git pull origin main 
git add src/main.c src/heap.c src/heap.h make.sh push.sh

echo "Message:"
read message

git commit -m "${message}"
git push origin main
