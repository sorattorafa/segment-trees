#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OP_SOMA 0
#define OP_SUBTRACAO 1
#define OP_MULTIPLICACAO 2
#define OP_DIVISAO 3
#define OP_MAX 4
#define OP_MIN 5

typedef struct SegmentTree {
    int *tree;
    int *arr;
    int size;
} SegmentTree;

int getMid(int start, int end) {
    return start + (end - start) / 2;
}

int queryOp(SegmentTree st, int node, int start, int end, int left, int right) {
    if (left <= start && right >= end) {
        return st.tree[node];
    }
    if (end < left || start > right) {
        return 0;
    }
    int mid = getMid(start, end);
    int leftSum = queryOp(st, 2 * node + 1, start, mid, left, right);
    int rightSum = queryOp(st, 2 * node + 2, mid + 1, end, left, right);
    return leftSum + rightSum;
}

void do_print(int op, int start, int end, SegmentTree st, int node){
    if (op == OP_SOMA) {
        printf("Soma do intervalo [%d, %d]: %d\n", start, end, st.tree[node]);
    } 
    else if (op == OP_SUBTRACAO) {
        printf("Subtracao do intervalo [%d, %d]: %d\n", start, end, st.tree[node]);
    }
    else if (op == OP_MULTIPLICACAO) {
        printf("Multiplicacao do intervalo [%d, %d]: %d\n", start, end, st.tree[node]);
    }
    else if (op == OP_DIVISAO) {
        printf("Divisao do intervalo [%d, %d]: %d\n", start, end, st.tree[node]);
    } 
    else if (op == OP_MAX) {
        printf("Maximo do intervalo [%d, %d]: %d\n", start, end, st.tree[node]);
    }
    else if (op == OP_MIN) {
        printf("Minimo do intervalo [%d, %d]: %d\n", start, end, st.tree[node]);
    }
}

void do_operation(SegmentTree st, int node, int op, int start, int end){
    int val1 = st.tree[2 * node + 1];
    int val2 = st.tree[2 * node + 2];
    
    if (op == OP_SOMA) {
        st.tree[node] = val1 + val2;
    } 
    else if (op == OP_SUBTRACAO) {
        st.tree[node] = val1 - val2;
    }
    else if (op == OP_MULTIPLICACAO) {
        st.tree[node] = val1 * val2;
    }
    else if (op == OP_DIVISAO) {
        st.tree[node] = val1 / val2;
    } 
    else if (op == OP_MAX) {
        if (val1 >val2) {
            st.tree[node] = val1;     
        } else {
            st.tree[node] = val2;   
        }
    }
    else if (op == OP_MIN) {
        if (val1 <val2) {
            st.tree[node] = val1;    
        } else {
            st.tree[node] = val2;   
        }   
    }

}

void buildSegmentTreeUtil(SegmentTree st, int node, int start, int end, int op) {
    if (start == end) {
        st.tree[node] = st.arr[start];
    } else {
        int mid = getMid(start, end);
        buildSegmentTreeUtil(st, 2 * node + 1, start, mid, op);
        buildSegmentTreeUtil(st, 2 * node + 2, mid + 1, end, op);

        do_operation(st, node, op, start, end);
        do_print(op, start, end, st, node);

    }
}

SegmentTree buildSegmentTree(int arr[], int n, int op) {
    SegmentTree st;
    st.arr = arr;
    st.size = n;

    int treeSize = 4 * n;
    st.tree = (int*)malloc(treeSize * sizeof(int));
    buildSegmentTreeUtil(st, 0, 0, n - 1, op);
    
    return st;
}

void defaultInput(){ //Mesmo vetor e operacao do artigo
    printf("* Default input *\n\n");
    
    int arr[] = {1, 3, -2, 8, -7};
    // int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;
    
    printf("Vetor de entrada:\n");
    for (i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    
    int op = OP_SOMA;
    printf("\n\nOperacao: Soma");
    printf("\n\n");
    
    clock_t start = clock();
    SegmentTree st = buildSegmentTree(arr, n, op);
    clock_t end = clock();
    double elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Arvore final: \n");
    for (int i = 0; i <= sizeof(st.tree) ; i++) {
        printf("%d\t", st.tree[i]);
    }
    printf("\n\n");

    free(st.tree);
    
    printf("Tempo de execucao: %.6f segundos\n", elapsed_time);
}

void customInput(){ //Vetor e operacao a definir
    int n;
    printf("* Custom input *\n\n");
    printf("Digite o tamanho do vetor de entrada: ");
    scanf("%d", &n);
    
    int arr[n];
    int i;
    
    for (i = 0; i < n; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    
    printf("\nVetor de entrada:\n");
    for (i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    
    int op;
    while (1) {
        printf("\n\nDigite a operacao desejada: \n");
        printf("0 - Soma\n");
        printf("1 - Subtracao\n");
        printf("2 - Multiplicacao\n");
        printf("3 - Divisao\n");
        printf("4 - Maximo\n");
        printf("5 - Minimo\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op != 0 && op != 1 && op != 2 && op != 3 && op != 4 && op != 5) {
            printf("\nOpcao invalida! Tente novamente.");
            continue;
        }
        else {
            break;  
        }
    }   
    
    printf("\n");
    
    clock_t start = clock();
    SegmentTree st = buildSegmentTree(arr, n, op);
    clock_t end = clock();
    double elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Arvore final: \n");
    for (int i = 0; i <= sizeof(st.tree) ; i++) {
        printf("%d\t", st.tree[i]);
    }
    printf("\n\n");

    free(st.tree);
    
    printf("Tempo de execucao: %.6f segundos\n", elapsed_time);
}

int main() {
    // defaultInput();
    customInput();
    return 0;
}
