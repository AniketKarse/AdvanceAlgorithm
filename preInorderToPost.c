#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
struct node{
	int val;
	struct node* left;
	struct node* right;
};
void postorder(struct node* root){
	if(!root) return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->val);
}

void freeTree(struct node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

struct node* PreInOrderToPost(int* preorder, int* inorder, int* p, int start, int end, int n){
	if(*p>=n || start>end) return NULL;
	int mid;
	for(int i=start;i<=end;i++){
		if(inorder[i]==preorder[*p]){
			mid = i;
			break;
		}
	}
	struct node* cur = (struct node*)malloc(sizeof(struct node));
	cur->val = preorder[(*p)++];
	cur->left = PreInOrderToPost(preorder, inorder, p, start, mid-1, n);
	cur->right = PreInOrderToPost(preorder, inorder, p, mid+1, end, n);
	return cur;
}
int main(){
	int n;
	scanf("%d", &n);
	int* preorder = (int*)malloc(n*sizeof(int));
	int* inorder = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		scanf("%d", &preorder[i]);
	}
	for(int i=0;i<n;i++){
		scanf("%d", &inorder[i]);
	}
	int index = 0;
	int* p = &index;
	struct node* head = PreInOrderToPost(preorder, inorder, p, 0, n-1, n);
	postorder(head);
	freeTree(head);
    free(preorder);
    free(inorder);
	return 0;
}
