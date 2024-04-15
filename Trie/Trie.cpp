struct Trie {
    struct Node {
        Node *child[26];
        int IsEnd, prefix;

        Node() {
            memset(child, 0, sizeof child);
            IsEnd = prefix = 0;
        }
    };

    Node *root = new Node();

    void insert(string &s) {
        Node *cur = root;
        for (auto i: s) {
            if (cur->child[i - 'a'] == 0)cur->child[i - 'a'] = new Node();
            cur = cur->child[i - 'a'];
            cur->prefix++;
        }
        cur->IsEnd++;
    }

    bool searchword(string &s) {
        Node *cur = root;
        for (auto i: s) {
            if (cur->child[i - 'a'] == 0)return false;
            cur = cur->child[i - 'a'];
        }
        return cur->IsEnd;
    }

    ll countword(string &s) {
        Node *cur = root;
        for (auto i: s) {
            if (cur->child[i - 'a'] == 0)return 0;
            cur = cur->child[i - 'a'];
        }
        return cur->IsEnd;
    }

    ll countprefix(string &s) {
        Node *cur = root;
        for (auto i: s) {
            if (cur->child[i - 'a'] == 0)return 0;
            cur = cur->child[i - 'a'];
        }
        return cur->prefix;
    }
};