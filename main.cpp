#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
struct loc
{int x,y;};
//is mouse colliding with object?
bool itin(int mousePosX, int mousePosY,sf::Vector2f PiecePos)
{
	return mousePosX <= PiecePos.x+100 && mousePosX >= PiecePos.x && mousePosY <= PiecePos.y+100 && mousePosY >= PiecePos.y;
}
//Moving function for control
void MovePiece(sf::Sprite &Piece, sf::Event event,bool &req)
{
	if(event.type==sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && 
			itin(event.mouseButton.x, event.mouseButton.y, Piece.getPosition())) req = true;
	else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		req=false;Piece.setPosition(((int)(Piece.getPosition().x+50)/100)*100,((int)(Piece.getPosition().y+50)/100)*100);
	}
	if(req && event.type == sf::Event::MouseMoved) 
		Piece.setPosition(event.mouseMove.x-50,event.mouseMove.y-50);
}
int getId(int input)
{
	if(input>0) return input-1;
	else if(input<0) return (input*-1)+5;
	else return 0;
}
int ReverseBoard[8][8]={/* Board Array (u can modify)*/
	 5, 4, 3, 1, 2, 3, 4, 5,
	 6, 6, 6, 6, 6, 6, 6, 6,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	-6,-6,-6,-6,-6,-6,-6,-6,
	-5,-4,-3,-1,-2,-3,-4,-5
};

class Piece
{
	private:
		int id;loc location; bool req;sf::Sprite spr;
		sf::RenderWindow *window;
	public:
		Piece(int d, loc locn, sf::Texture chessTexture[12],sf::RenderWindow *urWindow) : window(urWindow)
		{
			req=0;location = locn;id=d;
			spr.setTexture(chessTexture[getId(id)]);
			spr.setScale(100/45,100/45); spr.setPosition(sf::Vector2f(locn.x*100,locn.y*100));
		}
		void move(sf::Event event){MovePiece(spr,event,req);}
		void draw(){window->draw(spr);}
		bool getReq() const{return req;}
};

#define board ReverseBoard
int main()
{
	sf::RenderWindow window(sf::VideoMode(800,800),"Chess!");
	sf::Texture Pieces_Texture[12];//For Texture Parser
	sf::Texture BoardTexture; BoardTexture.loadFromFile("chesstable.jpg");
	std::vector<Piece> Pieces;
	//Texture Parser
	for(int i = 0;i<2;i++) for(int j = 0;j<6;j++) {
		Pieces_Texture[j+(i*6)].loadFromFile("chess_sprite.png",sf::IntRect(j*45,i*45,45,45));
		Pieces_Texture[j+(i*6)].setSmooth(true);
	}
	//Chess Pieces Generation
	for(int i = 0;i<8;i++) for(int j = 0;j<8;j++)
		if(board[i][j]!=0) Pieces.push_back(Piece(board[i][j],{i,j},Pieces_Texture,&window));
	//GAME!
	while(window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type==sf::Event::Closed) window.close();
			//Controls
			for(int i = 0;i<Pieces.size();i++) {Pieces[i].move(event);if(Pieces[i].getReq())break;}

		}
		//Printing
		window.clear();
		sf::Sprite chessTable; chessTable.setTexture(BoardTexture); chessTable.setScale(1,800/796);
		window.draw(chessTable);
		for(Piece  drawning : Pieces) drawning.draw();
		window.display();
	}
	return 0;
}
