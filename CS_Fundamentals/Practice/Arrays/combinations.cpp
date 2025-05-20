class Solution {
public:
    inline string GetLetters(char num, vector<string> letterList)
    {
        // Since letters[0] contains the letters for the number 2
        int letterIndex = (num - '0')-2;
        return letterList[letterIndex];
    }

    vector<string> letterCombinations(string digits) 
    {
        vector<string> letterList = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        // Vector for storing a combination to then store into result vector
        vector<string> temp;
        vector<string> result = {""};

        if(digits == "") return {};

        for(int i = 0; i < digits.size(); ++i)
        {
            // Get the first set of letters (if digits[1] = '2' then letters = "abc")
            string letters = GetLetters(digits[i], letterList);
            temp.clear();

            for(string& combination : result)
            {
                // Build the combination
                for(char letter : letters)
                {
                    temp.push_back(combination + letter);
                }
            }
            result = temp;
        }
        return result;
    }
};