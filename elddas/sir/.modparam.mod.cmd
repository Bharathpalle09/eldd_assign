savedcmd_/home/bharat/Desktop/elddas/sir/modparam.mod := printf '%s\n'   modparam.o | awk '!x[$$0]++ { print("/home/bharat/Desktop/elddas/sir/"$$0) }' > /home/bharat/Desktop/elddas/sir/modparam.mod
