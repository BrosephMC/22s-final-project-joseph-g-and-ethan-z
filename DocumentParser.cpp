//
// Created by jojog on 4/11/2022.
//

#include "DocumentParser.h"
#include <experimental/filesystem>

using namespace std;

void DocumentParser::ParseDocument(char *&file) {
    int maxCharCount = 500000;
    char wholeFile[maxCharCount];

    fstream data_file;
    data_file.open(file);
    data_file.getline(wholeFile, maxCharCount);
    data_file.close();
    cout << file << " is parsed" << endl;

    doc.Parse(wholeFile);
}

void DocumentParser::ParseText(IndexHandler &ih, const string& fileName) {

    istringstream ss(doc["text"].GetString());
    string word;

    string title = doc["title"].GetString();
    string date = doc["published"].GetString();
    cout << " Title: " << title << endl;
    cout << " Date published: " << date << endl;

    while (ss >> word){

        simplifyWord(word);

        //find stop words
        if(stopWords.find(word) != stopWords.end() || word.length() <= 0){
            //cout << " - STOPWORD";
        } else {
            string id = doc["uuid"].GetString();
            id += " ";
            id += fileName;
            ih.indexWord(word, id);
        }
    }
}

void DocumentParser::indexOrgsAndPersons(IndexHandler &ihORG, IndexHandler &ihPERSON, const string& fileName){

    string id = doc["uuid"].GetString();
    id += " ";
    id += fileName;

    cout << " Organizations: ";
    for (int i = 0; i < doc["entities"]["organizations"].Size(); i++){
        cout << doc["entities"]["organizations"][i]["name"].GetString() << ", ";
        ihORG.indexWord(doc["entities"]["organizations"][i]["name"].GetString(), id);
    }
    cout << endl;
    cout << " Persons: ";
    for (int i = 0; i < doc["entities"]["persons"].Size(); i++){
        cout << doc["entities"]["persons"][i]["name"].GetString() << ", ";
        ihPERSON.indexWord(doc["entities"]["persons"][i]["name"].GetString(), id);
    }
    cout << endl;
}

void DocumentParser::ParseDatabase(char *&path, IndexHandler &ih, IndexHandler &ihORG, IndexHandler &ihPERSON) {
//https://www.delftstack.com/howto/cpp/how-to-get-list-of-files-in-a-directory-cpp/

    DIR *dir; struct dirent *diread;
    vector<string> folders;

    //put contents of directory into a vector
    if ((dir = opendir(path)) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            folders.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        cout << "EXIT FAILURE" << endl;
    }

    //outputs the contents
    cout << " List of folders:" << endl;
    for (auto folder : folders){
        cout << folder << "| ";
    }
    cout << endl << endl;

    string folder;
    for(int i = 2; i < folders.size(); i++){

        folder = folders.at(i);
        //cout << folder << " < this is a folder" << endl;
        vector<string> files;

        //creates a path string to specified folder
        string appendedPathString = path;
        appendedPathString += "/";
        appendedPathString += folder;
        char* appendedPath = const_cast<char *>(appendedPathString.c_str());
        //cout << appendedPath << endl;

        //put file contents of directory into a vector
        if ((dir = opendir(appendedPath)) != nullptr) {
            while ((diread = readdir(dir)) != nullptr) {
                files.push_back(diread->d_name);
            }
            closedir (dir);
        } else {
            cout << "could not open dir of appended path" << endl;
            perror ("opendir");
            cout << "EXIT FAILURE" << endl;
        }

        //iterates through and parses each file
        for(int i = 2; i < files.size(); i++){
            string file = files.at(i);
            //cout << file << "| " << endl;

            //creates a path string to specified file
            string appendedPathString = appendedPath;
            appendedPathString += "/";
            appendedPathString += file;
            char* appendedPath = const_cast<char *>(appendedPathString.c_str());
            //cout << appendedPath << endl;

            ParseDocument(appendedPath);
            ParseText(ih, files.at(i));
            indexOrgsAndPersons(ihORG, ihPERSON, files.at(i));
        }

        cout << endl;
        cout << endl;
    }
}

void DocumentParser::simplifyWord(string &word) {
    //convert word to lower case characters
    //remove extra characters (keeps letters)

    for(int i = 0; i < word.length(); i++){
        word[i] = tolower(word[i]);
        if(word[i] < 97 || word[i] > 122){
            word.erase(i, 1);
            i--;
        }
    }

    Porter2Stemmer::stem(word);
}

DocumentParser::DocumentParser() {
    stopWords["a"] = "a";
    stopWords["able"] = "able";
    stopWords["about"] = "about";
    stopWords["above"] = "above";
    stopWords["abroad"] = "abroad";
    stopWords["according"] = "according";
    stopWords["accordingly"] = "accordingly";
    stopWords["across"] = "across";
    stopWords["actually"] = "actually";
    stopWords["adj"] = "adj";
    stopWords["after"] = "after";
    stopWords["afterwards"] = "afterwards";
    stopWords["again"] = "again";
    stopWords["against"] = "against";
    stopWords["ago"] = "ago";
    stopWords["ahead"] = "ahead";
    stopWords["ain't"] = "ain't";
    stopWords["all"] = "all";
    stopWords["allow"] = "allow";
    stopWords["allows"] = "allows";
    stopWords["almost"] = "almost";
    stopWords["alone"] = "alone";
    stopWords["along"] = "along";
    stopWords["alongside"] = "alongside";
    stopWords["already"] = "already";
    stopWords["also"] = "also";
    stopWords["although"] = "although";
    stopWords["always"] = "always";
    stopWords["am"] = "am";
    stopWords["amid"] = "amid";
    stopWords["amidst"] = "amidst";
    stopWords["among"] = "among";
    stopWords["amongst"] = "amongst";
    stopWords["an"] = "an";
    stopWords["and"] = "and";
    stopWords["another"] = "another";
    stopWords["any"] = "any";
    stopWords["anybody"] = "anybody";
    stopWords["anyhow"] = "anyhow";
    stopWords["anyone"] = "anyone";
    stopWords["anything"] = "anything";
    stopWords["anyway"] = "anyway";
    stopWords["anyways"] = "anyways";
    stopWords["anywhere"] = "anywhere";
    stopWords["apart"] = "apart";
    stopWords["appear"] = "appear";
    stopWords["appreciate"] = "appreciate";
    stopWords["appropriate"] = "appropriate";
    stopWords["are"] = "are";
    stopWords["aren't"] = "aren't";
    stopWords["around"] = "around";
    stopWords["as"] = "as";
    stopWords["a's"] = "a's";
    stopWords["aside"] = "aside";
    stopWords["ask"] = "ask";
    stopWords["asking"] = "asking";
    stopWords["associated"] = "associated";
    stopWords["at"] = "at";
    stopWords["available"] = "available";
    stopWords["away"] = "away";
    stopWords["awfully"] = "awfully";
    stopWords["back"] = "back";
    stopWords["backward"] = "backward";
    stopWords["backwards"] = "backwards";
    stopWords["be"] = "be";
    stopWords["became"] = "became";
    stopWords["because"] = "because";
    stopWords["become"] = "become";
    stopWords["becomes"] = "becomes";
    stopWords["becoming"] = "becoming";
    stopWords["been"] = "been";
    stopWords["before"] = "before";
    stopWords["beforehand"] = "beforehand";
    stopWords["begin"] = "begin";
    stopWords["behind"] = "behind";
    stopWords["being"] = "being";
    stopWords["believe"] = "believe";
    stopWords["below"] = "below";
    stopWords["beside"] = "beside";
    stopWords["besides"] = "besides";
    stopWords["best"] = "best";
    stopWords["better"] = "better";
    stopWords["between"] = "between";
    stopWords["beyond"] = "beyond";
    stopWords["both"] = "both";
    stopWords["brief"] = "brief";
    stopWords["but"] = "but";
    stopWords["by"] = "by";
    stopWords["came"] = "came";
    stopWords["can"] = "can";
    stopWords["cannot"] = "cannot";
    stopWords["cant"] = "cant";
    stopWords["can't"] = "can't";
    stopWords["caption"] = "caption";
    stopWords["cause"] = "cause";
    stopWords["causes"] = "causes";
    stopWords["certain"] = "certain";
    stopWords["certainly"] = "certainly";
    stopWords["changes"] = "changes";
    stopWords["clearly"] = "clearly";
    stopWords["c'mon"] = "c'mon";
    stopWords["co"] = "co";
    stopWords["co."] = "co.";
    stopWords["com"] = "com";
    stopWords["come"] = "come";
    stopWords["comes"] = "comes";
    stopWords["concerning"] = "concerning";
    stopWords["consequently"] = "consequently";
    stopWords["consider"] = "consider";
    stopWords["considering"] = "considering";
    stopWords["contain"] = "contain";
    stopWords["containing"] = "containing";
    stopWords["contains"] = "contains";
    stopWords["corresponding"] = "corresponding";
    stopWords["could"] = "could";
    stopWords["couldn't"] = "couldn't";
    stopWords["course"] = "course";
    stopWords["c's"] = "c's";
    stopWords["currently"] = "currently";
    stopWords["dare"] = "dare";
    stopWords["daren't"] = "daren't";
    stopWords["definitely"] = "definitely";
    stopWords["described"] = "described";
    stopWords["despite"] = "despite";
    stopWords["did"] = "did";
    stopWords["didn't"] = "didn't";
    stopWords["different"] = "different";
    stopWords["directly"] = "directly";
    stopWords["do"] = "do";
    stopWords["does"] = "does";
    stopWords["doesn't"] = "doesn't";
    stopWords["doing"] = "doing";
    stopWords["done"] = "done";
    stopWords["don't"] = "don't";
    stopWords["down"] = "down";
    stopWords["downwards"] = "downwards";
    stopWords["during"] = "during";
    stopWords["each"] = "each";
    stopWords["edu"] = "edu";
    stopWords["eg"] = "eg";
    stopWords["eight"] = "eight";
    stopWords["eighty"] = "eighty";
    stopWords["either"] = "either";
    stopWords["else"] = "else";
    stopWords["elsewhere"] = "elsewhere";
    stopWords["end"] = "end";
    stopWords["ending"] = "ending";
    stopWords["enough"] = "enough";
    stopWords["entirely"] = "entirely";
    stopWords["especially"] = "especially";
    stopWords["et"] = "et";
    stopWords["etc"] = "etc";
    stopWords["even"] = "even";
    stopWords["ever"] = "ever";
    stopWords["evermore"] = "evermore";
    stopWords["every"] = "every";
    stopWords["everybody"] = "everybody";
    stopWords["everyone"] = "everyone";
    stopWords["everything"] = "everything";
    stopWords["everywhere"] = "everywhere";
    stopWords["ex"] = "ex";
    stopWords["exactly"] = "exactly";
    stopWords["example"] = "example";
    stopWords["except"] = "except";
    stopWords["fairly"] = "fairly";
    stopWords["far"] = "far";
    stopWords["farther"] = "farther";
    stopWords["few"] = "few";
    stopWords["fewer"] = "fewer";
    stopWords["fifth"] = "fifth";
    stopWords["first"] = "first";
    stopWords["five"] = "five";
    stopWords["followed"] = "followed";
    stopWords["following"] = "following";
    stopWords["follows"] = "follows";
    stopWords["for"] = "for";
    stopWords["forever"] = "forever";
    stopWords["former"] = "former";
    stopWords["formerly"] = "formerly";
    stopWords["forth"] = "forth";
    stopWords["forward"] = "forward";
    stopWords["found"] = "found";
    stopWords["four"] = "four";
    stopWords["from"] = "from";
    stopWords["further"] = "further";
    stopWords["furthermore"] = "furthermore";
    stopWords["get"] = "get";
    stopWords["gets"] = "gets";
    stopWords["getting"] = "getting";
    stopWords["given"] = "given";
    stopWords["gives"] = "gives";
    stopWords["go"] = "go";
    stopWords["goes"] = "goes";
    stopWords["going"] = "going";
    stopWords["gone"] = "gone";
    stopWords["got"] = "got";
    stopWords["gotten"] = "gotten";
    stopWords["greetings"] = "greetings";
    stopWords["had"] = "had";
    stopWords["hadn't"] = "hadn't";
    stopWords["half"] = "half";
    stopWords["happens"] = "happens";
    stopWords["hardly"] = "hardly";
    stopWords["has"] = "has";
    stopWords["hasn't"] = "hasn't";
    stopWords["have"] = "have";
    stopWords["haven't"] = "haven't";
    stopWords["having"] = "having";
    stopWords["he"] = "he";
    stopWords["he'd"] = "he'd";
    stopWords["he'll"] = "he'll";
    stopWords["hello"] = "hello";
    stopWords["help"] = "help";
    stopWords["hence"] = "hence";
    stopWords["her"] = "her";
    stopWords["here"] = "here";
    stopWords["hereafter"] = "hereafter";
    stopWords["hereby"] = "hereby";
    stopWords["herein"] = "herein";
    stopWords["here's"] = "here's";
    stopWords["hereupon"] = "hereupon";
    stopWords["hers"] = "hers";
    stopWords["herself"] = "herself";
    stopWords["he's"] = "he's";
    stopWords["hi"] = "hi";
    stopWords["him"] = "him";
    stopWords["himself"] = "himself";
    stopWords["his"] = "his";
    stopWords["hither"] = "hither";
    stopWords["hopefully"] = "hopefully";
    stopWords["how"] = "how";
    stopWords["howbeit"] = "howbeit";
    stopWords["however"] = "however";
    stopWords["hundred"] = "hundred";
    stopWords["i'd"] = "i'd";
    stopWords["ie"] = "ie";
    stopWords["if"] = "if";
    stopWords["ignored"] = "ignored";
    stopWords["i'll"] = "i'll";
    stopWords["i'm"] = "i'm";
    stopWords["immediate"] = "immediate";
    stopWords["in"] = "in";
    stopWords["inasmuch"] = "inasmuch";
    stopWords["inc"] = "inc";
    stopWords["inc."] = "inc.";
    stopWords["indeed"] = "indeed";
    stopWords["indicate"] = "indicate";
    stopWords["indicated"] = "indicated";
    stopWords["indicates"] = "indicates";
    stopWords["inner"] = "inner";
    stopWords["inside"] = "inside";
    stopWords["insofar"] = "insofar";
    stopWords["instead"] = "instead";
    stopWords["into"] = "into";
    stopWords["inward"] = "inward";
    stopWords["is"] = "is";
    stopWords["isn't"] = "isn't";
    stopWords["it"] = "it";
    stopWords["it'd"] = "it'd";
    stopWords["it'll"] = "it'll";
    stopWords["its"] = "its";
    stopWords["it's"] = "it's";
    stopWords["itself"] = "itself";
    stopWords["i've"] = "i've";
    stopWords["just"] = "just";
    stopWords["k"] = "k";
    stopWords["keep"] = "keep";
    stopWords["keeps"] = "keeps";
    stopWords["kept"] = "kept";
    stopWords["know"] = "know";
    stopWords["known"] = "known";
    stopWords["knows"] = "knows";
    stopWords["last"] = "last";
    stopWords["lately"] = "lately";
    stopWords["later"] = "later";
    stopWords["latter"] = "latter";
    stopWords["latterly"] = "latterly";
    stopWords["least"] = "least";
    stopWords["less"] = "less";
    stopWords["lest"] = "lest";
    stopWords["let"] = "let";
    stopWords["let's"] = "let's";
    stopWords["like"] = "like";
    stopWords["liked"] = "liked";
    stopWords["likely"] = "likely";
    stopWords["likewise"] = "likewise";
    stopWords["little"] = "little";
    stopWords["look"] = "look";
    stopWords["looking"] = "looking";
    stopWords["looks"] = "looks";
    stopWords["low"] = "low";
    stopWords["lower"] = "lower";
    stopWords["ltd"] = "ltd";
    stopWords["made"] = "made";
    stopWords["mainly"] = "mainly";
    stopWords["make"] = "make";
    stopWords["makes"] = "makes";
    stopWords["many"] = "many";
    stopWords["may"] = "may";
    stopWords["maybe"] = "maybe";
    stopWords["mayn't"] = "mayn't";
    stopWords["me"] = "me";
    stopWords["mean"] = "mean";
    stopWords["meantime"] = "meantime";
    stopWords["meanwhile"] = "meanwhile";
    stopWords["merely"] = "merely";
    stopWords["might"] = "might";
    stopWords["mightn't"] = "mightn't";
    stopWords["mine"] = "mine";
    stopWords["minus"] = "minus";
    stopWords["miss"] = "miss";
    stopWords["more"] = "more";
    stopWords["moreover"] = "moreover";
    stopWords["most"] = "most";
    stopWords["mostly"] = "mostly";
    stopWords["mr"] = "mr";
    stopWords["mrs"] = "mrs";
    stopWords["much"] = "much";
    stopWords["must"] = "must";
    stopWords["mustn't"] = "mustn't";
    stopWords["my"] = "my";
    stopWords["myself"] = "myself";
    stopWords["name"] = "name";
    stopWords["namely"] = "namely";
    stopWords["nd"] = "nd";
    stopWords["near"] = "near";
    stopWords["nearly"] = "nearly";
    stopWords["necessary"] = "necessary";
    stopWords["need"] = "need";
    stopWords["needn't"] = "needn't";
    stopWords["needs"] = "needs";
    stopWords["neither"] = "neither";
    stopWords["never"] = "never";
    stopWords["neverf"] = "neverf";
    stopWords["neverless"] = "neverless";
    stopWords["nevertheless"] = "nevertheless";
    stopWords["new"] = "new";
    stopWords["next"] = "next";
    stopWords["nine"] = "nine";
    stopWords["ninety"] = "ninety";
    stopWords["no"] = "no";
    stopWords["nobody"] = "nobody";
    stopWords["non"] = "non";
    stopWords["none"] = "none";
    stopWords["nonetheless"] = "nonetheless";
    stopWords["noone"] = "noone";
    stopWords["no-one"] = "no-one";
    stopWords["nor"] = "nor";
    stopWords["normally"] = "normally";
    stopWords["not"] = "not";
    stopWords["nothing"] = "nothing";
    stopWords["notwithstanding"] = "notwithstanding";
    stopWords["novel"] = "novel";
    stopWords["now"] = "now";
    stopWords["nowhere"] = "nowhere";
    stopWords["obviously"] = "obviously";
    stopWords["of"] = "of";
    stopWords["off"] = "off";
    stopWords["often"] = "often";
    stopWords["oh"] = "oh";
    stopWords["ok"] = "ok";
    stopWords["okay"] = "okay";
    stopWords["old"] = "old";
    stopWords["on"] = "on";
    stopWords["once"] = "once";
    stopWords["one"] = "one";
    stopWords["ones"] = "ones";
    stopWords["one's"] = "one's";
    stopWords["only"] = "only";
    stopWords["onto"] = "onto";
    stopWords["opposite"] = "opposite";
    stopWords["or"] = "or";
    stopWords["other"] = "other";
    stopWords["others"] = "others";
    stopWords["otherwise"] = "otherwise";
    stopWords["ought"] = "ought";
    stopWords["oughtn't"] = "oughtn't";
    stopWords["our"] = "our";
    stopWords["ours"] = "ours";
    stopWords["ourselves"] = "ourselves";
    stopWords["out"] = "out";
    stopWords["outside"] = "outside";
    stopWords["over"] = "over";
    stopWords["overall"] = "overall";
    stopWords["own"] = "own";
    stopWords["particular"] = "particular";
    stopWords["particularly"] = "particularly";
    stopWords["past"] = "past";
    stopWords["per"] = "per";
    stopWords["perhaps"] = "perhaps";
    stopWords["placed"] = "placed";
    stopWords["please"] = "please";
    stopWords["plus"] = "plus";
    stopWords["possible"] = "possible";
    stopWords["presumably"] = "presumably";
    stopWords["probably"] = "probably";
    stopWords["provided"] = "provided";
    stopWords["provides"] = "provides";
    stopWords["que"] = "que";
    stopWords["quite"] = "quite";
    stopWords["qv"] = "qv";
    stopWords["rather"] = "rather";
    stopWords["rd"] = "rd";
    stopWords["re"] = "re";
    stopWords["really"] = "really";
    stopWords["reasonably"] = "reasonably";
    stopWords["recent"] = "recent";
    stopWords["recently"] = "recently";
    stopWords["regarding"] = "regarding";
    stopWords["regardless"] = "regardless";
    stopWords["regards"] = "regards";
    stopWords["relatively"] = "relatively";
    stopWords["respectively"] = "respectively";
    stopWords["right"] = "right";
    stopWords["round"] = "round";
    stopWords["said"] = "said";
    stopWords["same"] = "same";
    stopWords["saw"] = "saw";
    stopWords["say"] = "say";
    stopWords["saying"] = "saying";
    stopWords["says"] = "says";
    stopWords["second"] = "second";
    stopWords["secondly"] = "secondly";
    stopWords["see"] = "see";
    stopWords["seeing"] = "seeing";
    stopWords["seem"] = "seem";
    stopWords["seemed"] = "seemed";
    stopWords["seeming"] = "seeming";
    stopWords["seems"] = "seems";
    stopWords["seen"] = "seen";
    stopWords["self"] = "self";
    stopWords["selves"] = "selves";
    stopWords["sensible"] = "sensible";
    stopWords["sent"] = "sent";
    stopWords["serious"] = "serious";
    stopWords["seriously"] = "seriously";
    stopWords["seven"] = "seven";
    stopWords["several"] = "several";
    stopWords["shall"] = "shall";
    stopWords["shan't"] = "shan't";
    stopWords["she"] = "she";
    stopWords["she'd"] = "she'd";
    stopWords["she'll"] = "she'll";
    stopWords["she's"] = "she's";
    stopWords["should"] = "should";
    stopWords["shouldn't"] = "shouldn't";
    stopWords["since"] = "since";
    stopWords["six"] = "six";
    stopWords["so"] = "so";
    stopWords["some"] = "some";
    stopWords["somebody"] = "somebody";
    stopWords["someday"] = "someday";
    stopWords["somehow"] = "somehow";
    stopWords["someone"] = "someone";
    stopWords["something"] = "something";
    stopWords["sometime"] = "sometime";
    stopWords["sometimes"] = "sometimes";
    stopWords["somewhat"] = "somewhat";
    stopWords["somewhere"] = "somewhere";
    stopWords["soon"] = "soon";
    stopWords["sorry"] = "sorry";
    stopWords["specified"] = "specified";
    stopWords["specify"] = "specify";
    stopWords["specifying"] = "specifying";
    stopWords["still"] = "still";
    stopWords["sub"] = "sub";
    stopWords["such"] = "such";
    stopWords["sup"] = "sup";
    stopWords["sure"] = "sure";
    stopWords["take"] = "take";
    stopWords["taken"] = "taken";
    stopWords["taking"] = "taking";
    stopWords["tell"] = "tell";
    stopWords["tends"] = "tends";
    stopWords["th"] = "th";
    stopWords["than"] = "than";
    stopWords["thank"] = "thank";
    stopWords["thanks"] = "thanks";
    stopWords["thanx"] = "thanx";
    stopWords["that"] = "that";
    stopWords["that'll"] = "that'll";
    stopWords["thats"] = "thats";
    stopWords["that's"] = "that's";
    stopWords["that've"] = "that've";
    stopWords["the"] = "the";
    stopWords["their"] = "their";
    stopWords["theirs"] = "theirs";
    stopWords["them"] = "them";
    stopWords["themselves"] = "themselves";
    stopWords["then"] = "then";
    stopWords["thence"] = "thence";
    stopWords["there"] = "there";
    stopWords["thereafter"] = "thereafter";
    stopWords["thereby"] = "thereby";
    stopWords["there'd"] = "there'd";
    stopWords["therefore"] = "therefore";
    stopWords["therein"] = "therein";
    stopWords["there'll"] = "there'll";
    stopWords["there're"] = "there're";
    stopWords["theres"] = "theres";
    stopWords["there's"] = "there's";
    stopWords["thereupon"] = "thereupon";
    stopWords["there've"] = "there've";
    stopWords["these"] = "these";
    stopWords["they"] = "they";
    stopWords["they'd"] = "they'd";
    stopWords["they'll"] = "they'll";
    stopWords["they're"] = "they're";
    stopWords["they've"] = "they've";
    stopWords["thing"] = "thing";
    stopWords["things"] = "things";
    stopWords["think"] = "think";
    stopWords["third"] = "third";
    stopWords["thirty"] = "thirty";
    stopWords["this"] = "this";
    stopWords["thorough"] = "thorough";
    stopWords["thoroughly"] = "thoroughly";
    stopWords["those"] = "those";
    stopWords["though"] = "though";
    stopWords["three"] = "three";
    stopWords["through"] = "through";
    stopWords["throughout"] = "throughout";
    stopWords["thru"] = "thru";
    stopWords["thus"] = "thus";
    stopWords["till"] = "till";
    stopWords["to"] = "to";
    stopWords["together"] = "together";
    stopWords["too"] = "too";
    stopWords["took"] = "took";
    stopWords["toward"] = "toward";
    stopWords["towards"] = "towards";
    stopWords["tried"] = "tried";
    stopWords["tries"] = "tries";
    stopWords["truly"] = "truly";
    stopWords["try"] = "try";
    stopWords["trying"] = "trying";
    stopWords["t's"] = "t's";
    stopWords["twice"] = "twice";
    stopWords["two"] = "two";
    stopWords["un"] = "un";
    stopWords["under"] = "under";
    stopWords["underneath"] = "underneath";
    stopWords["undoing"] = "undoing";
    stopWords["unfortunately"] = "unfortunately";
    stopWords["unless"] = "unless";
    stopWords["unlike"] = "unlike";
    stopWords["unlikely"] = "unlikely";
    stopWords["until"] = "until";
    stopWords["unto"] = "unto";
    stopWords["up"] = "up";
    stopWords["upon"] = "upon";
    stopWords["upwards"] = "upwards";
    stopWords["us"] = "us";
    stopWords["use"] = "use";
    stopWords["used"] = "used";
    stopWords["useful"] = "useful";
    stopWords["uses"] = "uses";
    stopWords["using"] = "using";
    stopWords["usually"] = "usually";
    stopWords["v"] = "v";
    stopWords["value"] = "value";
    stopWords["various"] = "various";
    stopWords["versus"] = "versus";
    stopWords["very"] = "very";
    stopWords["via"] = "via";
    stopWords["viz"] = "viz";
    stopWords["vs"] = "vs";
    stopWords["want"] = "want";
    stopWords["wants"] = "wants";
    stopWords["was"] = "was";
    stopWords["wasn't"] = "wasn't";
    stopWords["way"] = "way";
    stopWords["we"] = "we";
    stopWords["we'd"] = "we'd";
    stopWords["welcome"] = "welcome";
    stopWords["well"] = "well";
    stopWords["we'll"] = "we'll";
    stopWords["went"] = "went";
    stopWords["were"] = "were";
    stopWords["we're"] = "we're";
    stopWords["weren't"] = "weren't";
    stopWords["we've"] = "we've";
    stopWords["what"] = "what";
    stopWords["whatever"] = "whatever";
    stopWords["what'll"] = "what'll";
    stopWords["what's"] = "what's";
    stopWords["what've"] = "what've";
    stopWords["when"] = "when";
    stopWords["whence"] = "whence";
    stopWords["whenever"] = "whenever";
    stopWords["where"] = "where";
    stopWords["whereafter"] = "whereafter";
    stopWords["whereas"] = "whereas";
    stopWords["whereby"] = "whereby";
    stopWords["wherein"] = "wherein";
    stopWords["where's"] = "where's";
    stopWords["whereupon"] = "whereupon";
    stopWords["wherever"] = "wherever";
    stopWords["whether"] = "whether";
    stopWords["which"] = "which";
    stopWords["whichever"] = "whichever";
    stopWords["while"] = "while";
    stopWords["whilst"] = "whilst";
    stopWords["whither"] = "whither";
    stopWords["who"] = "who";
    stopWords["who'd"] = "who'd";
    stopWords["whoever"] = "whoever";
    stopWords["whole"] = "whole";
    stopWords["who'll"] = "who'll";
    stopWords["whom"] = "whom";
    stopWords["whomever"] = "whomever";
    stopWords["who's"] = "who's";
    stopWords["whose"] = "whose";
    stopWords["why"] = "why";
    stopWords["will"] = "will";
    stopWords["willing"] = "willing";
    stopWords["wish"] = "wish";
    stopWords["with"] = "with";
    stopWords["within"] = "within";
    stopWords["without"] = "without";
    stopWords["wonder"] = "wonder";
    stopWords["won't"] = "won't";
    stopWords["would"] = "would";
    stopWords["wouldn't"] = "wouldn't";
    stopWords["yes"] = "yes";
    stopWords["yet"] = "yet";
    stopWords["you"] = "you";
    stopWords["you'd"] = "you'd";
    stopWords["you'll"] = "you'll";
    stopWords["your"] = "your";
    stopWords["you're"] = "you're";
    stopWords["yours"] = "yours";
    stopWords["yourself"] = "yourself";
    stopWords["yourselves"] = "yourselves";
    stopWords["you've"] = "you've";
    stopWords["zero"] = "zero";
}
