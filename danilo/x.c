#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define MAX_WORDS 100  // Define um limite para o número de palavras

typedef struct s_element t_element;
typedef struct s_element
{
	char		*identifier;

	double	  cameraangle;

	double	  bright;
	int		 r;
	int		 g;
	int		 b;

	double		x;
	double		y;
	double		z;
	double		normalized_x;
	double		normalized_y;
	double		normalized_z;

	double	  diametre;
	double	  height;

	t_element   *prev;
	t_element   *next;

} t_element;

typedef struct s_elements{
	int A;
	int C;
	int L;
	int sp;
	int pl;
	int cy;

	t_element *el_A;
	t_element *el_C;
	t_element *el_L;

	t_element   *start;
	t_element   *last;

} t_elements;


size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int is_element(char *input);
int whitch_element(char *input);
char *convert_to_element(int input);
char *ft_strchr(const char *s, int c);
double string_to_double(const char *str, int *valida);
double get_bright(char *input);
int count_occurrences(const char *str, char c);
void get_rgb(char *input, int *rgb);
void create_element(char **matriz, t_elements *lista, int *i, int pos);

size_t	ft_strlen(const char *s){
	unsigned int	len;

	len = 0;
	while (s != NULL && s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	int		index;

	new = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!new)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		new[index] = s[index];
		index++;
	}
	new[index] = '\0';
	return (new);
}

int is_element(char *input){
	if(strcmp(input, "A") == 0 || strcmp(input, "C") == 0 ||
		strcmp(input, "L") == 0 || strcmp(input, "sp") == 0 ||
		strcmp(input, "pl") == 0 || strcmp(input, "cy") == 0)
		return 1;
	return 0;
}

int whitch_element(char *input){
	if(strcmp(input, "A") == 0)
		return 1;
	else if(strcmp(input, "C") == 0)
		return 2;
	else if(strcmp(input, "L") == 0)
		return 3;
	else if(strcmp(input, "sp") == 0)
		return 4;
	else if(strcmp(input, "pl") == 0)
		return 5;
	else if(strcmp(input, "cy") == 0)
		return 6;
	return 0;
}

char *convert_to_element(int input){
	if(input == 1)
		return ("A");
	if(input == 2)
		return ("C");
	if(input == 3)
		return ("L");
	if(input == 4)
		return ("sp");
	if(input == 5)
		return ("pl");
	if(input == 6)
		return ("cy");
	return NULL;
}

char *ft_strchr(const char *s, int c) {
	char *s_copy = (char *)s;
	while (*s_copy) {
		if (*s_copy == (char)c)
			return s_copy;
		s_copy++;
	}
	if ((char)c == '\0')
		return s_copy;
	return NULL;
}

size_t my_strspn(const char *str, const char *accept) {
	const char *s = str;
	size_t count = 0;

	while (*s && ft_strchr(accept, *s) != NULL) {
		count++;
		s++;
	}

	return count;
}

size_t ft_strcspn(const char *str, const char *reject) {
	const char *s = str;
	size_t count = 0;

	while (*s && ft_strchr(reject, *s) == NULL) {
		count++;
		s++;
	}

	return count;
}

char *ft_strtok(char *str, const char *delim) {
	static char *next_token = NULL;
	char *token_start, *token_end;

	if (str != NULL) {
		next_token = str;
	}
	if (next_token == NULL)
		return NULL;

	// Ignoramos delimitadores no início
	token_start = next_token + my_strspn(next_token, delim);
	if (*token_start == '\0') {
		next_token = NULL;
		return NULL;
	}

	// Encontramos o fim do token
	token_end = token_start + ft_strcspn(token_start, delim);
	if (*token_end != '\0') {
		*token_end = '\0';
		next_token = token_end + 1;
	} else {
		next_token = NULL;
	}

	return token_start;
}

// Função para ler a próxima linha do arquivo
char *get_next_line(FILE *fp) {
	char *line = malloc(BUFFER_SIZE);
	if (!line) return NULL;

	if (fgets(line, BUFFER_SIZE, fp) == NULL) {
		free(line);
		return NULL;
	}

	return line;
}

// Função para processar todo o arquivo e tratar quebras de linha como espaços
char *reformat_content(FILE *file) {
	char *line, *result = malloc(BUFFER_SIZE);
	if (!result) return NULL;
	result[0] = '\0';  // Inicializa a string de resultado como vazia

	int lastWasSpace = 1;  // Supõe que o último caractere foi um espaço
	size_t used = 0;  // Controle do tamanho usado no buffer

	while ((line = get_next_line(file)) != NULL) {
		for (int i = 0; line[i] != '\0'; i++) {
			if (!isspace(line[i])) {
				if (lastWasSpace && used > 0) {
					result[used++] = ' ';
					if (used == BUFFER_SIZE - 1) break;
				}
				result[used++] = line[i];
				if (used == BUFFER_SIZE - 1) break;
				lastWasSpace = 0;
			} else {
				if (!lastWasSpace) lastWasSpace = 1;
			}
		}
		free(line);
		if (used == BUFFER_SIZE - 1) break;
	}
	
	result[used] = '\0';
	return result;
}

// Função para dividir a string em palavras e armazená-las em uma matriz
char **split_into_words(char *content, int *word_count) {
	char **words = malloc(MAX_WORDS * sizeof(char *));
	char *token = strtok(content, " ");
	int count = 0;

	while (token != NULL && count < MAX_WORDS) {

		words[count++] = strdup(token);
		token = strtok(NULL, " ");
	}

	*word_count = count;
	return words;
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	index;
	int	sign;

	sign = 1;
	index = 0;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || nptr[index] == 32)
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			sign = sign * -1;
		index++;
	}
	result = 0;
	while (nptr[index] != '\0' && (nptr[index] >= 48 && nptr[index] <= 57))
	{
		result = result * 10 + nptr[index] - '0';
		index++;
	}
	return (result * sign);
}

double string_to_double(const char *str, int *valida) {
	double result = 0.0;
	int sign = 1;
	int decimal = 0; // Indica se já encontramos o ponto decimal
	double fraction = 0.1; // Fator de multiplicação para casas decimais

	// Verifica se o número é negativo
	if (*str == '-') {
		sign = -1;
		str++;
	}

	while (*str != '\0') {
		// Se encontrar o ponto decimal, ativa o flag decimal
		if (*str == '.') {
			decimal = 1;
			str++;
			continue;
		}
		// Verifica se o caractere é um dígito
		if (*str >= '0' && *str <= '9') {
			// Se decimal for 0, significa que estamos lidando com a parte inteira
			if (!decimal) {
				result = result * 10.0 + (*str - '0');
			} else { // Se decimal for 1, estamos lidando com a parte decimal
				result = result + fraction * (*str - '0');
				fraction /= 10.0; // Atualiza o fator de multiplicação para a próxima casa decimal
			}
		} else { // Caractere inválido
			printf("Erro: Caractere inválido na string.\n");
			*valida = -1;
			return 0.0;
		}
		str++;
	}

	return sign * result;
}

double get_bright(char *input){

	double retur;
	int valida;
	retur = string_to_double(input, &valida);

	if(!valida)
	{
		printf("\n-------------------------------------\nERRO NO BRIGHT - Parametro não numérico\n-------------------------------------\n");
		exit(-1);
	}

	if(retur < 0.0 || retur > 1.0)
	{
		printf("\n-------------------------------------\nERRO NO BRIGHT - Parametro fora de range (0.0 <-> 1.0)\n-------------------------------------\n");
		exit(-1);
	}

	return retur;
}

int count_occurrences(const char *str, char c) {
	int count = 0;

	// Percorre a string caractere por caractere
	while (*str != '\0') {
		// Se o caractere atual for igual ao caractere que estamos contando
		if (*str == c) {
			count++;
		}
		str++; // Move para o próximo caractere da string
	}

	return count;
}

void get_rgb(char *input, int *rgb){

	char *token;
	char *str_copy = strdup(input); // Copia a string de entrada para evitar alterações indesejadas
	int i = 0;

	if(count_occurrences(input, ',') != 2 || count_occurrences(input, '.') != 0){
		printf("\n-------------------------------------\nERRO NO RGB - Parametro com ',' incorretas ou .\n-------------------------------------\n");
		exit(-1);

	}

	// Separa a string em tokens usando a vírgula como delimitador
	token = ft_strtok(str_copy, ",");
	while (token != NULL) {
		rgb[i] = ft_atoi(token); // Converte o token para um inteiro e armazena na matriz RGB
		if(rgb[i] < 0 || rgb[i] > 255){
			printf("\n-------------------------------------\nERRO NO RGB - Parametro com range incorreto(0 <-> 255)\n-------------------------------------\n");
			exit(-1);
		}
		i++;
		token = ft_strtok(NULL, ",");
	}
	free(str_copy); // Libera a memória alocada para a cópia da string
}

void get_coordinate(char *input, double *coordinate){

	char *token;
	char *str_copy = strdup(input); // Copia a string de entrada para evitar alterações indesejadas
	int i;
	int valida;

	i = 0;
	// Separa a string em tokens usando a vírgula como delimitador
	token = ft_strtok(str_copy, ",");
	while (token != NULL) {
		coordinate[i++] = string_to_double(token, &valida); // Converte o token para um inteiro e armazena na matriz RGB
		if(!valida)
		{
			printf("\n-------------------------------------\nERRO NA COORDENADA - Parametro não numérico\n-------------------------------------\n");
			exit(-1);
		}
		token = ft_strtok(NULL, ",");
	}
	free(str_copy); // Libera a memória alocada para a cópia da string
}

void get_normalized_3d(char *input, double *normalized_3d){

	char *token;
	char *str_copy = strdup(input); // Copia a string de entrada para evitar alterações indesejadas
	int i;
	int valida;

	i = 0;
	// Separa a string em tokens usando a vírgula como delimitador
	token = ft_strtok(str_copy, ",");
	while (token != NULL) {
		normalized_3d[i] = string_to_double(token, &valida); // Converte o token para um inteiro e armazena na matriz RGB
		if(!valida)
		{
			printf("\n-------------------------------------\nERRO NO Normalized 3d - Parametro não numérico\n-------------------------------------\n");
			exit(-1);
		}
		if(normalized_3d[i] < -1.0 || normalized_3d[i] > 1.0)
		{
			printf("\n-------------------------------------\nERRO NO Normalized 3d - Parametro fora de range (-1.0 <-> 1.0)\n-------------------------------------\n");
			exit(-1);
		}
		i++;
		token = ft_strtok(NULL, ",");
	}
	free(str_copy); // Libera a memória alocada para a cópia da string
}

double get_fov(char *input){

	double retur;
	int valida;
	retur = string_to_double(input, &valida);

	if(!valida)
	{
		printf("\n-------------------------------------\nERRO NO FOV(Camera) - Parametro não numérico\n-------------------------------------\n");
		exit(-1);
	}

	if(retur < 0.0 || retur > 180.0)
	{
		printf("\n-------------------------------------\nERRO NO FOV(Camera) - Parametro fora de range (0.0 <-> 180.0)\n-------------------------------------\n");
		exit(-1);
	}
	return retur;
}

double get_floatnumber(char *input){

	double retur;
	int valida;

	retur = string_to_double(input, &valida);
	if(!valida)
	{
		printf("\n-------------------------------------\nERRO NO get_floatnumber - Parametro não numérico\n-------------------------------------\n");
		exit(-1);
	}
	return retur;
}

void create_element(char **matriz, t_elements *lista, int *i, int pos){

	t_element *element = (t_element *)malloc(sizeof(t_element)); // Aloca memória para um elemento da lista
	int rgb[3];
	double coordinate[3];
	double normalized_3d[3];
	double cameraangle;

	if(strcmp(matriz[*i], "A") == 0){
		element->identifier = ft_strdup("A");
		element->bright = get_bright(matriz[*i+1]);
		get_rgb(matriz[*i+2], rgb);
		element->r = rgb[0];
		element->g = rgb[1];
		element->b = rgb[2];
		lista->A += 1;
		*i += 2;
	}else if(strcmp(matriz[*i], "C") == 0){
		element->identifier = ft_strdup("C");
		get_coordinate(matriz[*i+1], coordinate);
		element->x = coordinate[0];
		element->y = coordinate[1];
		element->z = coordinate[2];
		get_normalized_3d(matriz[*i+2], normalized_3d);
		element->normalized_x = normalized_3d[0];
		element->normalized_y = normalized_3d[1];
		element->normalized_z = normalized_3d[2];
		element->cameraangle = get_fov(matriz[*i+3]);
		*i += 3;
		lista->C += 1;
	}else if(strcmp(matriz[*i], "L") == 0){
		element->identifier = ft_strdup("L");
		get_coordinate(matriz[*i+1], coordinate);
		element->x = coordinate[0];
		element->y = coordinate[1];
		element->z = coordinate[2];
		element->bright = get_bright(matriz[*i+2]);
		get_rgb(matriz[*i+3], rgb);
		element->r = rgb[0];
		element->g = rgb[1];
		element->b = rgb[2];
		*i += 3;
		lista->L += 1;
	}else if(strcmp(matriz[*i], "sp") == 0){
		element->identifier = ft_strdup("sp");
		get_coordinate(matriz[*i+1], coordinate);
		element->x = coordinate[0];
		element->y = coordinate[1];
		element->z = coordinate[2];
		element->diametre = get_floatnumber(matriz[*i+2]);
		get_rgb(matriz[*i+3], rgb);
		element->r = rgb[0];
		element->g = rgb[1];
		element->b = rgb[2];
		*i += 3;
		lista->sp += 1;
	}else if(strcmp(matriz[*i], "pl") == 0){
		element->identifier = ft_strdup("pl");
		get_coordinate(matriz[*i+1], coordinate);
		element->x = coordinate[0];
		element->y = coordinate[1];
		element->z = coordinate[2];
		get_normalized_3d(matriz[*i+2], normalized_3d);
		element->normalized_x = normalized_3d[0];
		element->normalized_y = normalized_3d[1];
		element->normalized_z = normalized_3d[2];
		get_rgb(matriz[*i+3], rgb);
		element->r = rgb[0];
		element->g = rgb[1];
		element->b = rgb[2];
		*i += 3;
		lista->pl += 1;
	}else if(strcmp(matriz[*i], "cy") == 0){
		element->identifier = ft_strdup("cy");

		get_coordinate(matriz[*i+1], coordinate);
		element->x = coordinate[0];
		element->y = coordinate[1];
		element->z = coordinate[2];
		get_normalized_3d(matriz[*i+2], normalized_3d);
		element->normalized_x = normalized_3d[0];
		element->normalized_y = normalized_3d[1];
		element->normalized_z = normalized_3d[2];
		element->diametre = get_floatnumber(matriz[*i+3]);
		element->height = get_floatnumber(matriz[*i+4]);
		get_rgb(matriz[*i+5], rgb);
		element->r = rgb[0];
		element->g = rgb[1];
		element->b = rgb[2];
		*i += 5;
		lista->cy += 1;
	}

	if (pos == 0) {
		if (lista->start == NULL) {  // Verifica se a lista está vazia
			lista->start = element;
		} else {
			lista->last->next = element;  // Encadeia corretamente se a lista não está vazia
			element->prev = lista->last;
		}
		lista->last = element;
	} else {
		element->next = NULL;
		element->prev = lista->last;
		lista->last->next = element;
		lista->last = element;
	}
}


int main() {
	FILE *file = fopen("scene.rt", "r");

	t_elements *lista = (t_elements *)malloc(sizeof(t_elements)); // Aloca memória para um elemento da lista

	if (lista == NULL) {
		printf("Erro ao alocar memória.\n");
		return 1; // Indica erro
	}

	if (!file) {
		perror("Failed to open file");
		return EXIT_FAILURE;
	}

	char *reformatted_content = reformat_content(file);
	fclose(file);
	
	if (reformatted_content) {
		// printf("Reformatted content: \n%s\n", reformatted_content);
		
		int word_count;
		char **matriz = split_into_words(reformatted_content, &word_count);
		int inicial = 0;

		// printf("Words:\n");
		for (int i = 0; i < word_count; i++) {
			// printf("\n%s (valor de i - %d)", matriz[i], i);
			if(is_element(matriz[i])){
				if(lista->start  == NULL)
				{
					// printf(" - Chamada 0");
					create_element(matriz, lista, &i, 0);
				}else{
					// printf(" - Chamada 1");
					create_element(matriz, lista, &i, 1);
				}
			}
		}
		printf("\nLuz Ambiente - %d\nLuz Camera - %d\nLuz Luz - %d\nLuz Espera - %d\nLuz Plano - %d\nLuz Cilindro - %d\n",lista->A, lista->C,lista->L,lista->sp,lista->pl,lista->cy);

		t_element *el = lista->start; // Começa com o primeiro elemento da lista
		int loop = 0;

		while (el) {
			printf("\n------------------------");
			printf("\n		  Elemento %d ", loop++);
			printf("\nNome - %s", el->identifier);

			printf("\nBright - %f", el->bright);
			printf("\nRGB - %d,%d,%d", el->r, el->g, el->b);

			printf("\nCamera - %f", el->cameraangle);

			printf("\nCoordenadas - x(%f),y(%f),z(%f)", el->x, el->y, el->z);
			printf("\n3D Normalizado - x(%f),y(%f),z(%f)", el->normalized_x, el->normalized_y, el->normalized_z);

			printf("\nDiametro(%f)", el->diametre);
			printf("\nAltura(%f)", el->height);

			printf("\n");
			el = el->next; // Move para o próximo elemento da lista
		}

		if(lista->A != 1 || lista->C != 1 || lista->L != 1){
			printf("\n-------------------------------------\nERRO NA QTD de Parametro OBRIGATÓRIOS\n-------------------------------------\n");
			exit(-1);
		}

		// Liberar a matriz e cada palavra
		for (int i = 0; i < word_count; i++) {
			free(matriz[i]);
		}

		free(lista);
		free(matriz);
		free(reformatted_content);
	}

	return EXIT_SUCCESS;
}
