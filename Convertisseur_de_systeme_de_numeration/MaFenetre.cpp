#include "MaFenetre.h"
MaFenetre::MaFenetre( QWidget *parent ) : QDialog( parent )
{
// 1. Instancier les widgets
valeur = new QLineEdit(this);
resultat = new QLabel(this);
unite = new QLabel(this);
choixConversion = new QComboBox(this);
bConvertir = new QPushButton(QString::fromUtf8("Convertir"), this);
bQuitter = new QPushButton(QString::fromUtf8("Quitter"), this);

// 2. Personnaliser les widgets
valeur->setStyleSheet("color: #0a214c; background-color: #fffdfd;");
valeur->clear();
QFont font("Liberation Sans", 12, QFont::Bold);
choixConversion->setFont(font);
choixConversion->addItem(QString::fromUtf8("Binaire -> Décimal"));
choixConversion->addItem(QString::fromUtf8("Décimal -> Binaire"));
choixConversion->addItem(QString::fromUtf8("Binaire -> hexadecimal"));
choixConversion->addItem(QString::fromUtf8("hexadecimal -> Binaire"));
choixConversion->addItem(QString::fromUtf8("Decimal -> hexadecimal"));
choixConversion->addItem(QString::fromUtf8("hexadecimal -> Decimal"));
resultat->setStyleSheet("color: #0a214c;");
unite->setStyleSheet("color: #0a214c;");

// 3. Instancier les layouts
QHBoxLayout *hLayout1 = new QHBoxLayout;
QHBoxLayout *hLayout2 = new QHBoxLayout;
QVBoxLayout *mainLayout = new QVBoxLayout;

// 4. Positionner les widgets dans les layouts
hLayout1->addWidget(valeur);
hLayout1->addWidget(choixConversion);
hLayout1->addWidget(resultat);
hLayout1->addWidget(unite);
hLayout2->addWidget(bConvertir);
hLayout2->addWidget(bQuitter);
mainLayout->addLayout(hLayout1);
mainLayout->addLayout(hLayout2);
setLayout(mainLayout);

// 5. Connecter les signaux et slots
connect(bConvertir, SIGNAL(clicked()), this, SLOT(convertir()));
connect(this, SIGNAL(actualiser()), this, SLOT(convertir()));
connect(choixConversion, SIGNAL(currentIndexChanged(int)), this, SLOT(permuter()));
connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
// bonus : conversion automatique
// connect(valeur, SIGNAL(textChanged(const QString &)), this, SLOT(convertir()));

// 6. Personnaliser la fenêtre
setWindowTitle(QString::fromUtf8("Convertisseur Binaire/Décimal/Hexadecimal"));
adjustSize();
emit actualiser();
}

// 7. Définir les slots
void MaFenetre::convertir()
{
    QString nombre = valeur->text();
    if (nombre.isEmpty())
    {
        resultat->setText(QString::fromUtf8("--.--"));
        afficherUnite();
        return;
    }

    switch (choixConversion->currentIndex())
    {
        case BinaireTODecimal:
        {
            bool ok;
            int decimal = nombre.toInt(&ok, 2);
            if (ok)
            {
                resultat->setText(QString::number(decimal));
            }
            else
            {
                resultat->setText(QString::fromUtf8("Erreur"));
            }
        }
        break;

        case DecimalTOBinaire:
        {
            bool ok;
            int decimal = nombre.toInt(&ok, 10);
            if (ok)
            {
                resultat->setText(QString::number(decimal, 2));
            }
            else
            {
                resultat->setText(QString::fromUtf8("Erreur"));
            }
        }
        break;

        case BinaireToHexadecimal:
        {
            bool ok;
            int decimal = nombre.toInt(&ok, 2);
            if (ok)
            {
                resultat->setText(QString::number(decimal, 16).toUpper());
            }
            else
            {
                resultat->setText(QString::fromUtf8("Erreur"));
            }
        }
        break;

        case HexadecimalToBinaire:
        {
            bool ok;
            int decimal = nombre.toInt(&ok, 16);
            if (ok)
            {
                resultat->setText(QString::number(decimal, 2));
            }
            else
            {
                resultat->setText(QString::fromUtf8("Erreur"));
            }
        }
        break;

        case DecimalToHexadecimal:
        {
            bool ok;
            int decimal = nombre.toInt(&ok, 10);
            if (ok)
            {
                resultat->setText(QString::number(decimal, 16).toUpper());
            }
            else
            {
                resultat->setText(QString::fromUtf8("Erreur"));
            }
        }
        break;

        case HexadecimalToDecimal:
        {
            bool ok;
            int decimal = nombre.toInt(&ok, 16);
            if (ok)
            {
                resultat->setText(QString::number(decimal));
            }
            else
            {
                resultat->setText(QString::fromUtf8("Erreur"));
            }
        }
        break;

    }
    afficherUnite();
}

void MaFenetre::permuter()
{
    if (resultat->text() != "--.--")
    {
        valeur->setText(resultat->text());
        emit actualiser();
    }
    afficherUnite();
}

// 8. Définir les méthodes
void MaFenetre::afficherUnite()
{
    switch (choixConversion->currentIndex())
    {
        case BinaireTODecimal:
            unite->setText(QString::fromUtf8(" (Décimal)"));
            break;
        case DecimalTOBinaire:
            unite->setText(QString::fromUtf8(" (Binaire)"));
            break;
        case BinaireToHexadecimal:
            unite->setText(QString::fromUtf8(" (Hexadecimal)"));
            break;
        case HexadecimalToBinaire:
            unite->setText(QString::fromUtf8(" (Binaire)"));
            break;
        case DecimalToHexadecimal:
            unite->setText(QString::fromUtf8(" (Hexadecimal)"));
            break;
        case HexadecimalToDecimal:
            unite->setText(QString::fromUtf8(" (Decimal)"));
            break;
    }
}
