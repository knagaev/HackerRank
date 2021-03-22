#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


inline string ltrim_copy(const string& str, char c = ' ')
{
    string newStr { str };
    newStr.erase(0, newStr.find_first_not_of(c));
    return newStr;
}

inline string rtrim_copy(const string& str, char c = ' ')
{
    string newStr{ str };
    newStr.erase(newStr.find_last_not_of(' ') + 1);
    return newStr;
}

inline string trim_copy(const string& str, char left = ' ', char right = ' ')
{
    return str.substr(str.find_first_not_of(left), str.find_last_not_of(right));
}


class Tag
{
public:
    string getName() { return m_tagName; }
    //void setName(string tagName) { m_tagName = tagName; return; }
    
    void addAttribute(string attributeName, string attributeValue) { m_attributes[attributeName] = attributeValue; return; }
    string getAttribute(string tagName)
    {
        auto it = m_attributes.find(tagName);
        if (it != end(m_attributes))
            return (*it).second;
        else
            return "Not Found!";
    }

    void addTag(Tag* tag) { m_tags[tag->getName()] = tag; return; }
    Tag* getTag(string tagName) 
    { 
        auto it = m_tags.find(tagName); 
        if (it != end(m_tags))
            return (*it).second;
        else
            return nullptr;
    }

    static Tag* createTag(string tagLine);

private:
    string m_tagName;
    map<string, string> m_attributes;   // value -> name
    map<string, Tag*> m_tags;   // tagName -> Tag*

    Tag(string tagName) : m_tagName(tagName) {}
};

Tag* Tag::createTag(string tagLine)
{
    string cleanTagLine = trim_copy(tagLine, '<', '>');

    auto endPos = cleanTagLine.find(' ');

    auto newTag = new Tag(cleanTagLine.substr(0, endPos));

    auto currentPos = endPos;
    auto firstQuotationPos = cleanTagLine.find('"', currentPos);
    while (firstQuotationPos != string::npos)
    {
        auto secondQuotationPos = cleanTagLine.find('"', firstQuotationPos + 1);

        string attributeLine = cleanTagLine.substr(currentPos, secondQuotationPos - currentPos);

        auto attributeName = trim_copy(attributeLine.substr(0, attributeLine.find("=")));
        auto attributeValueLine = attributeLine.substr(attributeLine.find("=") + 1);
        auto attributeValue = trim_copy(trim_copy(attributeValueLine), '"', '"');

        newTag->addAttribute(attributeName, attributeValue);
        currentPos = secondQuotationPos + 1;
        
        firstQuotationPos = cleanTagLine.find('"', currentPos);
    }

    return newTag;
}

int main() {
    
    int n, q;

    cin >> n >> q;
    cin.ignore();

    string tagLine;
    vector<Tag*> st;

    Tag* rootTag = Tag::createTag("<>");;
    st.push_back(rootTag);

    for (int i = 0; i < n; ++i)
    {
        getline(cin, tagLine);
        if (tagLine.substr(0, 2) == "</")
        {
            st.pop_back();
        }
        else
        {
            auto newTag = Tag::createTag(tagLine);
            st.back()->addTag(newTag);
            st.push_back(newTag);
        }
    }

    string queryLine;
    for (int j = 0; j < q; ++j)
    {
        getline(cin, queryLine);

        auto tagPathLine = queryLine.substr(0, queryLine.find("~"));

        Tag* neededTag = st.back();
        auto currentPos = 0;
        while (true)
        {
            auto dotPos = tagPathLine.find(".", currentPos);
            auto tagName = tagPathLine.substr(currentPos, dotPos - currentPos);
            neededTag = neededTag->getTag(tagName);
            if (neededTag == nullptr)
            {
                cout << "Not Found!" << endl;
                break;
            }
            if (dotPos == string::npos) break;
            currentPos = dotPos + 1;
        }

        
        if (neededTag != nullptr)
        {
          auto attributeName = queryLine.substr(queryLine.find("~") + 1);
          cout << neededTag->getAttribute(attributeName) << endl;
        }
    }

    return 0;
}
