## Como usar ?

Faça o download desta pasta e, caso esteja no Windows, rode `python -m pip install -r requirements.txt` para instalar as dependências.

Se você está no Linux, rode `pip3 install -r requirements.txt`.

Depois disso, você pode testar o script de ajuste de curva com 4 exemplos de entrada:

Para Linux:

```sh
python3 ajuste_de_curva.py < entrada_linear.txt # Entrada para ajuste de curva linear
python3 ajuste_de_curva.py < entrada_exponencial.txt # Entrada para ajuste de curva exponential
python3 ajuste_de_curva.py < entrada_linear_youtube.txt # Entrada para ajuste de curva linear do youtube
python3 ajuste_de_curva.py < entrada_exponencial_youtube.txt # Entrada para ajuste de curva exponential do youtube
```

Para Windows:

```cmd
REM talvez seja py invés de python o comando
python ajuste_de_curva.py < entrada_linear.txt
python ajuste_de_curva.py < entrada_exponencial.txt
python ajuste_de_curva.py < entrada_linear_youtube.txt
python ajuste_de_curva.py < entrada_exponencial_youtube.txt
```

[Vídeo - 7. Método dos Mínimos Quadrados - Caso Linear](https://www.youtube.com/watch?v=0o_wuKE-mm4&ab_channel=quemsabefaz)

[Vídeo - 9. Método dos Mínimos Quadrados - Caso Exponencial](https://www.youtube.com/watch?v=CgBpe6h0pDw&ab_channel=quemsabefaz)
