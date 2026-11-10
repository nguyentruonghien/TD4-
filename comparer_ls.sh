#!/bin/sh
# Compare ./mon_ls -R avec ls -lR (tri "C", meme format de date)
export LC_ALL=C
TMP=$(mktemp -d) || exit 1; trap 'rm -rf "$TMP"' EXIT      # fichiers temporaires prives (pas de nom fixe dans /tmp)
cd td-test || exit 1
../mon_ls -R . 2>/dev/null | sed -E 's/ +/ /g' > "$TMP"/mon_ls.cmp
ls -lR --time-style='+%Y-%m-%d %H:%M' . 2>/dev/null | sed -E 's/ +/ /g' > "$TMP"/ls.cmp
diff "$TMP"/ls.cmp "$TMP"/mon_ls.cmp && echo "IDENTIQUE" || echo "DIFFERENCES (voir ci-dessus)"
