{
int number;
number = atoi("1-fundo");
if(number <= 7){
_compile_and_insert_new_shader("shaders/1-fundo", number - 1);
}
number = atoi("2-top");
if(number <= 7){
_compile_and_insert_new_shader("shaders/2-top", number - 1);
}
number = atoi("3-bot");
if(number <= 7){
_compile_and_insert_new_shader("shaders/3-bot", number - 1);
}
number = atoi("4-digito");
if(number <= 7){
_compile_and_insert_new_shader("shaders/4-digito", number - 1);
}
number = atoi("5-zindex");
if(number <= 7){
_compile_and_insert_new_shader("shaders/5-zindex", number - 1);
}
number = atoi("6-zimagens");
if(number <= 7){
_compile_and_insert_new_shader("shaders/6-zimagens", number - 1);
}
number = atoi("7-tile");
if(number <= 7){
_compile_and_insert_new_shader("shaders/7-tile", number - 1);
}
}
