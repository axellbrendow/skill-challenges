package app;

import java.io.File;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.FileChooser;
import javafx.stage.Screen;
import javafx.stage.Stage;

public class App extends Application {
    public static final Algoritmo[] algoritmos = {
        new MenorPreco(),
        new MenorDistancia(),
        new ViagemAoRedor(),
        new IntersecaoDeRotas()
    };

    public static final FileChooser fileChooser = new FileChooser();
    public static File distancesFile = null;
    public static File pricesFile = null;

    public MenuButton createAlgorithmsMenu() {
        final MenuItem[] menuItems = new MenuItem[algoritmos.length];
        MenuItem menuItem;
        int i = 0;

        for (final Algoritmo algoritmo : algoritmos) {
            menuItem = new MenuItem(algoritmo.nome);
            menuItem.setOnAction(e -> algoritmo.rodar());
            menuItems[i++] = menuItem;
        }

        return new MenuButton("Escolha um algoritmo", null, menuItems);
    }

    private static void carregarDistancias(ActionEvent e, Stage stage) {
        distancesFile = fileChooser.showOpenDialog(stage);
    }

    private static void carregarPrecos(ActionEvent e, Stage stage) {
        pricesFile = fileChooser.showOpenDialog(stage);
    }

    public static void main(final String[] args) throws Exception {
        launch();
    }

    @Override
    public void start(final Stage stage) throws Exception {
        final Rectangle2D bounds = Screen.getPrimary().getVisualBounds();

        final VBox root = new VBox();

        final Image mapa = new Image(new File("src/app/mapa.jpg").toURI().toString());
        final ImageView mapaView = new ImageView(mapa);
        stage.widthProperty().addListener(
            (obs, antigaLargura, novaLargura) -> mapaView.setFitWidth(novaLargura.doubleValue()));
        mapaView.setFitWidth(bounds.getWidth());
        mapaView.setPreserveRatio(true);
        mapaView.setSmooth(true);
        mapaView.setCache(true);

        final HBox btnsBox = new HBox();
        btnsBox.minHeight(bounds.getHeight() - mapaView.getLayoutBounds().getHeight());
        final Button btnDistancias = new Button("Carregar distâncias");
        btnDistancias.setOnAction(e -> carregarDistancias(e, stage));
        final Button btnPrecos = new Button("Carregar preços");
        btnPrecos.setOnAction(e -> carregarPrecos(e, stage));
        btnsBox.getChildren().addAll(createAlgorithmsMenu(), btnDistancias, btnPrecos);

        root.getChildren().addAll(mapaView, btnsBox);

        final Scene scene = new Scene(root);
        stage.setTitle("Trabalho grafos");
        stage.setScene(scene);
        stage.setMaximized(true);
        stage.show();
    }
}
