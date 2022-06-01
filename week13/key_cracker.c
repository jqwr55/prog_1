#define MAX_CIPHER 4096
#define READ_SIZE 256
#define KEY_SIZE 8

#include <stdio.h>
#include <unistd.h>
#include <string.h>

double compute_avg_word_size(const char cipher[], int cipher_size){

	int size = 0;

	for (int i = 0; i < cipher_size; i++)
		if (cipher[i] == ' ')
			++size;

	return (double)cipher_size / size;

}

int is_clear_text(const char cipher[], int cipher_size){

	double word_size = compute_avg_word_size(cipher, cipher_size);

	int proper_size = word_size < 9.0 && word_size > 6.0;

	int word_found = strcasestr (cipher, "nem") && strcasestr (cipher, "hogy") &&
					 strcasestr (cipher, "az") && strcasestr (cipher, "Ha");

	return proper_size && word_found;
}

void compute_xor(const char key[], int key_size, char cipher[], int cipher_size) {

	int key_index = 0;

	for (int i = 0; i < cipher_size; i++){
		cipher[i] = cipher[i] ^ key[key_index];
		key_index = (key_index + 1) % key_size;
	}
}

int xor_crack(const char key[], int key_size, char cipher[], int cipher_size){

	compute_xor(key, key_size, cipher, cipher_size);
	return is_clear_text(cipher, cipher_size);

}

int main(){

	char key[KEY_SIZE];
	char cipher[MAX_CIPHER];
	char* p = cipher;
	int read_bytes;

	while ( (read_bytes = 
		read ( 0, (void*) p, 
		(p - cipher + READ_SIZE <
		MAX_CIPHER) ? READ_SIZE : cipher + MAX_CIPHER - p )) )

	p += read_bytes;

	for (int i = 0; i < MAX_CIPHER - (p - cipher); ++i) {

		cipher[p - cipher + i] = '\0';
	}

	for (int ii = '0'; ii <= '9'; ++ii)
		for (int ji = '0'; ji <= '9'; ++ji)
			for (int ki = '0'; ki <= '9'; ++ki)
				for (int li = '0'; li <= '9'; ++li)
					for (int mi = '0'; mi <= '9'; ++mi) 
						for (int ni = '0'; ni <= '9'; ++ni)
							for (int oi = '0'; oi <= '9'; ++oi)
								for (int pi = '0'; pi <= '9'; ++pi) {
									key[0] = ii;
									key[1] = ji;
									key[2] = ki;
									key[3] = li;
									key[4] = mi;
									key[5] = ni;
									key[6] = oi;
									key[7] = pi;

					if (xor_crack(key, KEY_SIZE, cipher, p - cipher))
						printf(
							"key: [%c%c%c%c%c%c%c%c]\nclear text: [%s\n]",
							ii, ji, ki, li, mi, ni, oi, pi, cipher
						);

					compute_xor(key, KEY_SIZE, cipher, p - cipher);

				}

	return 0;
}