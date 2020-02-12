#include "test_runner.h"

#include <vector>

using namespace std;

class Log {
public:
	Log(string message) {
		cout << message << " started\n";
		this->message = message;
	}
	~Log() {
		cout << message << " finished\n";
	}
private:
	string message;
};

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	//Log a("SplitIntoSentences");
	vector<Sentence<Token>> text;
	text.push_back(Sentence<Token>());

	size_t currentVector = 0;

	for (auto oneToken = tokens.begin(); oneToken != tokens.end(); oneToken++) {
		//Log loop("for loop");
		if (oneToken->IsEndSentencePunctuation())  {
			text[currentVector].push_back(move(*oneToken));
			while (next(oneToken) != tokens.end() && next(oneToken)->IsEndSentencePunctuation()) {
				oneToken++;
				text[currentVector].push_back(move(*oneToken));
			}
			if (next(oneToken) != tokens.end()) {
				text.push_back(Sentence<Token>());
				currentVector++;
			}
		} else {
			text[currentVector].push_back(move(*oneToken));
		}
	}
	
	return text;
}


struct TestToken {
	string data;
	bool is_end_sentence_punctuation = false;

	bool IsEndSentencePunctuation() const {
	return is_end_sentence_punctuation;
	}
	bool operator==(const TestToken& other) const {
		return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
	}
	TestToken(const TestToken&) = delete;
	TestToken& operator=(const TestToken&) = delete;

	TestToken(TestToken&&) = default;
	TestToken& operator=(TestToken&&) = default;
};

ostream& operator<<(ostream& stream, const TestToken& token) {
	return stream << token.data;
}

void TestSplitting() {
	{
		vector<TestToken> result;
		result.push_back({"!", true});
		result.push_back({"Split"});
		result.push_back({"into"});
		result.push_back({"sentences"});
		result.push_back({"!"});

		vector<Sentence<TestToken>> expected;
		expected.push_back(Sentence<TestToken>());
		expected.push_back(Sentence<TestToken>());
		expected[0].push_back({"!", true});
		expected[1].push_back({"Split"});
		expected[1].push_back({"into"});
		expected[1].push_back({"sentences"});
		expected[1].push_back({"!"});

		ASSERT_EQUAL(SplitIntoSentences(move(result)), expected);
	}

	{
		vector<TestToken> result;
		result.push_back({"Split"});
		result.push_back({"into"});
		result.push_back({"sentences"});
		result.push_back({"!", true});

		vector<Sentence<TestToken>> expected;
		expected.push_back(Sentence<TestToken>());
		expected[0].push_back({"Split"});
		expected[0].push_back({"into"});
		expected[0].push_back({"sentences"});
		expected[0].push_back({"!", true});

		ASSERT_EQUAL(SplitIntoSentences(move(result)), expected);
	}

	{
		vector<TestToken> result;
		result.push_back({"Split"});
		result.push_back({"into"});
		result.push_back({"sentences"});
		result.push_back({"!", true});
		result.push_back({"!", true});
		result.push_back({"!", true});
		result.push_back({"Without"});
		result.push_back({"copies"});
		result.push_back({".", true});

		vector<Sentence<TestToken>> expected;
		expected.push_back(Sentence<TestToken>());
		expected.push_back(Sentence<TestToken>());
		expected[0].push_back({"Split"});
		expected[0].push_back({"into"});
		expected[0].push_back({"sentences"});
		expected[0].push_back({"!", true});
		expected[0].push_back({"!", true});
		expected[0].push_back({"!", true});

		expected[1].push_back({"Without"});
		expected[1].push_back({"copies"});
		expected[1].push_back({".", true});
		ASSERT_EQUAL(SplitIntoSentences(move(result)), expected);
	}

	{
		vector<TestToken> result;
		result.push_back({"!", true});
		result.push_back({"!", true});
		result.push_back({"!", true});
		result.push_back({"Split"});
		result.push_back({"into"});
		result.push_back({"sentences"});
		result.push_back({"!", true});
		result.push_back({"!", true});
		result.push_back({"!", true});
		result.push_back({"?", true});
		result.push_back({".", true});
		result.push_back({"Without"});
		result.push_back({"copies"});
		result.push_back({".", true});
		result.push_back({"Without"});
		result.push_back({"special"});
		result.push_back({"char"});
		result.push_back({"!", true});
		result.push_back({"!", true});

		vector<Sentence<TestToken>> expected;
		expected.push_back(Sentence<TestToken>());
		expected.push_back(Sentence<TestToken>());
		expected.push_back(Sentence<TestToken>());
		expected.push_back(Sentence<TestToken>());
		expected[0].push_back({"!", true});
		expected[0].push_back({"!", true});
		expected[0].push_back({"!", true});

		expected[1].push_back({"Split"});
		expected[1].push_back({"into"});
		expected[1].push_back({"sentences"});
		expected[1].push_back({"!", true});
		expected[1].push_back({"!", true});
		expected[1].push_back({"!", true});
		expected[1].push_back({"?", true});
		expected[1].push_back({".", true});

		expected[2].push_back({"Without"});
		expected[2].push_back({"copies"});
		expected[2].push_back({".", true});
		
		expected[3].push_back({"Without"});
		expected[3].push_back({"special"});
		expected[3].push_back({"char"});
		expected[3].push_back({"!", true});
		expected[3].push_back({"!", true});
		ASSERT_EQUAL(SplitIntoSentences(move(result)), expected);
	}

	/*
	ASSERT_EQUAL(
	SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
	vector<Sentence<TestToken>>({
		{{"Split"}, {"into"}, {"sentences"}, {"!"}}
	})
	);

	ASSERT_EQUAL(
	SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
	vector<Sentence<TestToken>>({
		{{"Split"}, {"into"}, {"sentences"}, {"!", true}}
	})
	);

	ASSERT_EQUAL(
	SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
	vector<Sentence<TestToken>>({
		{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
		{{"Without"}, {"copies"}, {".", true}},
	})
	);
	*/
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSplitting);
	return 0;
}
