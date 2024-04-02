#include "Level.h"

void Level::AddBras(float x, float y, bool up, std::string color)
{
	auto bras = std::make_unique<Bras>(x, y, up, world.get(), int(vecteurbras.size()) + 2, color);
	vecteurbras.push_back(std::move(bras));
}

Level::Level(int level) :
	level(level)
{
	pugi::xml_document doc;
	pugi::xml_node node;
	auto num = std::to_string(level);
	std::string link = "resources/Level" + num + ".xml";
	std::string name = "Level" + num;
	if (auto result = doc.load_file(link.c_str()); !result) {
		std::cerr << "Could not open file" << link << "because " << result.description() << std::endl;
	}
	else if (level > 7 || level < 1) {
		std::cerr << "No such level";
	}
	node = doc.child(name.c_str());
	//Vecteur gravite
	const b2Vec2 gravity(0.0f, -9.81f);
	//Creation du monde
	world = std::make_unique<b2World>(gravity);

	//Creation du sol
	double xfloor = node.child("Floor").attribute("x").as_double();
	double yfloor = node.child("Floor").attribute("y").as_double();
	std::cout << xfloor << " " << yfloor << "\n";
	double lengthfloor = node.child("Floor").attribute("length").as_double();
	double widthfloor = node.child("Floor").attribute("width").as_double();
	colorfloor = node.child("Floor").attribute("color").as_string();
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(float(xfloor), float(yfloor));
	groundBody = world->CreateBody(&groundBodyDef);
	//Consistance du sol
	b2PolygonShape groundBox;
	groundBox.SetAsBox(float(lengthfloor)/2, float(widthfloor)/2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	groundBody->CreateFixture(&fixtureDef);

	//Creation de la chipie
	double xchipie = node.child("Chipie").attribute("x").as_double();
	double ychipie = node.child("Chipie").attribute("y").as_double();
	double rchipie = node.child("Chipie").attribute("r").as_double();
	double speedchipie = node.child("Chipie").attribute("speed").as_double();
	std::string colorchipie = node.child("Chipie").attribute("color").as_string();
	chipie = std::make_unique<Chipie>(colorchipie, rchipie, xchipie, ychipie, speedchipie, world.get());

	for (pugi::xml_node bras : node.children("Bras")) {
		double xbras = bras.attribute("x").as_double();
		double ybras = bras.attribute("y").as_double();
		bool upbras = bras.attribute("up").as_bool();
		std::string colorbras = bras.attribute("color").as_string();
		AddBras(float(xbras), float(ybras), upbras, colorbras);
	}
	

	nbBras = int(vecteurbras.size());
}

b2World* Level::getWorld() const
{
	return world.get();
}

void Level::drawWorld(sf::RenderWindow& window, sf::View view) const
{
	b2Fixture* fixture = groundBody->GetFixtureList();
	float width = 0;
	float length = 0;
	while (fixture != nullptr) {
		if (b2Shape* shape = fixture->GetShape(); shape->GetType() == b2Shape::e_polygon) {
			auto const* polygonShape = dynamic_cast<b2PolygonShape*>(shape);
			b2Vec2 size = polygonShape->m_vertices[2] - polygonShape->m_vertices[0];
			width = size.y;
			length = size.x;
		}
		fixture = fixture->GetNext();
	}
	/*
    float xchipie = chipie->GetBody()->GetPosition().x*30 - float(window.getSize().x) / static_cast<float>(4);
	float ychipie = chipie->GetBody()->GetPosition().y*30 + 2 * float(window.getSize().y) / static_cast<float>(3);
	float xf = (groundBody->GetPosition().x - length/2 -xchipie/30)*30;
	float yf = -(groundBody->GetPosition().y + width/2 -ychipie/30)*30;
	sf::RectangleShape shape(sf::Vector2f(length*30, width*30));
	shape.setFillColor(which_color(&colorfloor));
	shape.setPosition(xf, yf);
	window.draw(shape);
	chipie->draw(window);
	for (int i = 0; i < nbBras; i++) {
		vecteurbras[i]->draw(window, xchipie, ychipie);
	}
    */
    float xchipie = chipie->GetBody()->GetPosition().x*30;
    float ychipie = -(chipie->GetBody()->GetPosition().y*30);
    float xf = (groundBody->GetPosition().x - length/2)*30;
    float yf = -(groundBody->GetPosition().y + width/2)*30;
    sf::RectangleShape shape(sf::Vector2f(length*30, width*30));
    shape.setFillColor(which_color(&colorfloor));
    shape.setPosition(xf, yf);
    window.draw(shape);
    chipie->draw(window, xchipie, ychipie);
    for (int i = 0; i < nbBras; i++) {
        vecteurbras[i]->draw(window, 0, 0);
    }

    view.setCenter(xchipie + float(window.getSize().x) / 4.f, ychipie);
    window.setView(view);

}

Bras* Level::getBras(int i) const
{
	return vecteurbras[i].get();
}

Chipie* Level::getChipie() const
{
	return chipie.get();
}

int Level::getNbBras() const
{
	return nbBras;
}

// TODO : (DONE) 4. Supprimer les StoryTeller 1 à 5, faire que le texte fasse partie du niveau... avec les 2 fonctions qui suivent

std::string Level::getStory() const {
    std::string chapter1 = R"(Après avoir fait une bonne farce à M.Chatouille et M.Farceur, qui s'est mis à la peinture,
Mme.Chipie était toute contente d'elle, elle se sentait orgueilleuse et espiègle.
Parfait pour commencer son anniversaire !

Oh non, M.Chatouille vous en veut, esquivez ses bras pour ne pas qu'il vous fasse tordre de rire !
Attention votre taille a augmenté !)";
    std::string chapter2 = R"(Nous sommes déjà en milieu de matinée et personne n'a souhaité l'anniversaire de Mme.Chipie !
Mme.Chipie ne se sent plus orgueuilleuse, elle se met en colère !
Oh non ce maudit M.Farceur l'a peinte en rouge !

Vous avez un coeur de pierre, profitez de cette vie supplémentaire !)";
    std::string chapter3 = R"(Dans la rue vers midi, Mme.Chipie aperçoit une petite fille, un cadeau dans les mains,
la jalousie de Mme.Chipie prend le dessus, Mme.Chipie devient toute verte de jalousie !

Vous pouvez courir plus vite, en voulant rattraper ce cadeau convoité !)";
    std::string chapter4 = R"(Et si tout le monde avait oublié l'anniversaire de Mme Chipie ?
Oh non ! Tout le monde ? Mme.Chipie devient terrifiée à cette idée.
Le violet va bien a Mme.Chipie.

Vous pouvez sursauter de peur à tout instant, vous sautez plus haut !)";
    std::string chapter5 = R"(Nous arrivons en début de soirée,
Mme.Chipie rentre chez elle triste car tout le monde a oublié son anniversaire
Le bleu lui permet de se fondre dans la nuit afin que les villageois ne voient pas la tristesse de Mme.Chipie

Vous vous faites tout petit pour ne pas qu'on vous voit)";
    std::string chapter6 = R"("Ah, je me sens toute vide. Personne ne m'aime ! Personne ne pense à moi !"
Mme.Chipie se dit en se dirigeant chez elle. "Si seulement quelqu'un me faisait un câlin..."
Elle commence à voir la vie en gris, fade et sans couleur.

Vous avez un besoin urgent d'affection ! Laissez M. Chatouille vous reconforter dans ses bras !)";
    std::string ending = R"(En poussant la porte de chez elle, elle sent une odeur étrange, puis en allumant la lumière,
tous ses amis étaient là, ils l'attendaient pour fêter son anniversaire ! M.Farceur était là !
Et c'est pour cela que M.Chatouille l'avait occupée toute la journée !
Mme.Chipie se mit à pleurer, mais de joie cette fois-ci !)";
    switch (level) {
        case 1:
            return chapter1;
            break;
        case 2:
            return chapter2;
            break;
        case 3:
            return chapter3;
            break;
        case 4:
            return chapter4;
            break;
        case 5:
            return chapter5;
            break;
        case 6:
            return chapter6;
            break;
        case 7:
            return ending;
            break;
        default:
            std::cout << "Numéro de niveau inexistant!" << std::endl;
            break;
    }
}

void Level::showStory(sf::RenderWindow& window, const sf::Font& font, sf::View view) const {
    sf::Text text;
    text.setFont(font);
    std::string ch_str = getStory();

    text.setString(sf::String::fromUtf8(ch_str.begin(), ch_str.end()));
    text.setPosition(0, -2000);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Blue);

    window.setView(view);
    window.draw(text);
}
