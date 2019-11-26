printf("Ingresar dato a eliminar: ");
        scanf("%d", &dato);
        Beliminar(Raiz, dato, &flag, &aux);
        if(aux == NULL)
          printf("No se encontró el dato\n");
        else{
          if(aux->izq == NULL && aux->der == NULL && Raiz == aux){
            Raiz = NULL;
            free(aux);
          }else{
            if(aux->izq == NULL && aux->der == NULL)
              borrarRaiz(Raiz, aux);
            else
              delete(aux, &bandera);
          }
          printf("Se ha eliminado correctamente\n");
        }


void Beliminar(Nodo* Raiz, int dato, int* flag, Nodo** aux){
  if(Raiz != NULL && *flag == 0){
    Nodo* aux2 = Raiz;
    Beliminar(Raiz->izq, dato, flag, aux);
    if(Raiz->dato == dato){
      *aux = aux2;
      *flag = 1;
    }
    Beliminar(Raiz->der, dato, flag, aux);
  }
}
void delete(Nodo* aux, int* bandera){
  Nodo* aux2;
  int aux3;
  if(*bandera == 0 && aux->izq != NULL && aux->izq->izq == NULL && aux->izq->der == NULL){
    aux2 = aux->izq;
    aux3 = aux->dato;
    aux->dato = aux2->dato;
    aux2->dato = aux3;
    aux->izq = NULL;
    *bandera = 1;
    free(aux2);
    return;
  }
  if(*bandera == 0 && aux->izq == NULL && aux->der != NULL && aux->der->izq == NULL && aux->der->der == NULL){
    aux2 = aux->der;
    aux3 = aux->dato;
    aux->dato = aux2->dato;
    aux2->dato = aux3;
    aux->der = NULL;
    *bandera = 1;
    free(aux2);
    return;
  }
  if(*bandera == 0 && aux->izq != NULL){
    aux2 = aux->izq;
    aux3 = aux->dato;
    aux->dato = aux2->dato;
    aux2->dato = aux3;
    aux = aux2;
    delete(aux, bandera);
  }
  if(*bandera == 0 && aux->izq == NULL && aux->der != NULL){
    aux2 = aux->der;
    aux3 = aux->dato;
    aux->dato = aux2->dato;
    aux2->dato = aux3;
    aux = aux2;
    delete(aux, bandera);
  }
}
void borrarRaiz(Nodo* Raiz, Nodo* aux){
  if(Raiz != NULL){
    if(Raiz->der == aux){
      Raiz->der = NULL;
      free(aux);
      return;
    }
    if(Raiz->izq == aux){
      Raiz->izq = NULL;
      free(aux);
      return;
    }
    if(Raiz->izq != NULL){
      borrarRaiz(Raiz->izq, aux);
    }
    if(Raiz->der != NULL){
      borrarRaiz(Raiz->der, aux);
    }
  }
}
