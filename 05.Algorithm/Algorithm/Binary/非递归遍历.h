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