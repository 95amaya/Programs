echo "1. show the list of files from * input command"
for file in "$@"; do
    echo "$file"
done

echo -e "\n2. show the list of fruit in program"
for fruit in orange apple grape; do
    echo "$fruit"
done

echo -e "\n3. show the list of files from ls command in program"
for file in $(ls -a *); do
    echo "$file"
done