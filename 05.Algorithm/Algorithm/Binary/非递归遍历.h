vector<int> preorderTraversal(TreeNode* root) {
	vector<int> res;
	if(root == NULL)
		return res;

	stack<TreeNode*> stack;
	stack.push(root);
	while(!stack.empty()){
		TreeNode* curNode = stack.top();
		stack.pop();
		res.push_back(curNode->val);

		if(curNode->right)
			stack.push(curNode->right);
		if(curNode->left)
			stack.push(curNode->left);
	}
	return res;
}

vector<int> inorderTraversal(TreeNode* root) {
	vector<int> res;
	if( root == NULL )
		return res;

	stack<TreeNode*> stack;
	TreeNode* cur = root;
	while(cur != NULL || !stack.empty()){

		while(cur != NULL){
			stack.push(cur);
			cur = cur->left;
		}

		cur = stack.top();
		stack.pop();
		res.push_back(cur->val);
		cur = cur->right;

	}
	return res;
}

vector<int> postorderTraversal(TreeNode* root) {
	vector<int> res;
	if(root == NULL)
		return res;

	stack<TreeNode*> stack, output;

	TreeNode* p = root;
	while(p != NULL || !stack.empty()){
		if(p != NULL){
			stack.push(p);
			output.push(p);
			p = p->right;
		}
		else{
			p = stack.top();
			stack.pop();
			p = p->left;
		}
	}

	while(!output.empty()){
		res.push_back((output.top())->val);
		output.pop();
	}

	return res;
}

vector<int> postorderTraversal2(TreeNode *root)
{
	stack<TreeNode *> st;
	vector<int> result;
	if (root == NULL)
		return result;
	st.push(root);
	while (!st.empty())
	{
		TreeNode *node = st.top();
		st.pop();
		result.push_back(node->val);
		if (node->left)
			st.push(node->left); // 相对于前序遍历，这更改一下入栈顺序 （空节点不入栈）
		if (node->right)
			st.push(node->right); // 空节点不入栈
	}
	reverse(result.begin(), result.end()); // 将结果反转之后就是左右中的顺序了
	return result;
}