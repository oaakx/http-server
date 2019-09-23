# Simultaneously tries to save index.html
# using 10000 instances of curl

mkdir trash
pushd trash
eq 1 10000 | xargs -n1 -P10000 bash -c 'i=$0; url="http://localhost:8080/index.html"; filename="index-${i}.html"; curl -s --http1.1 -o $filename $url'
popd
