export GITHUB_ORG=bmstu-iu8-cpp-sem-3

apk add groff util-linux
git clone \
  --config transfer.fsckobjects=false \
  --config receive.fsckobjects=false \
  --config fetch.fsckobjects=false \
  https://github.com/github/hub.git
cd hub && make install prefix=/usr/local && cd ..
git config --global hub.protocol https

npm install -g git-run
ln -s `npm bin -g`/gr `npm bin -g`/gmr

hub api -X GET /user/repos | jq -r '.[] .full_name' | grep ${GITHUB_ORG} | grep lab | grep -v xx | xargs -n 1 hub clone

find . -type d -name "lab*" | grep -v "template" | xargs gmr +@${GITHUB_ORG}

gmr @${GITHUB_ORG} hub status
gmr @${GITHUB_ORG} hub remote add template https://github.com/${GITHUB_ORG}/lab-xx-template.git
gmr @${GITHUB_ORG} hub fetch template master
gmr @${GITHUB_ORG} hub rebase template/master
gmr @${GITHUB_ORG} hub push -f origin master
