#pragma once
#include "hashing.h"

class arquivo
{
public:
	void abrirProduto(produto cadastro_p[1000], produto cadastro_ps[1000]);
	void abrirCompras(compra cadastro[1000]);
	void fecharProduto(produto cadastro_p[1000]);
	void fecharCompras(compra cadastro[1000]);
};