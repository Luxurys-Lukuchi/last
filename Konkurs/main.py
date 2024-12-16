from transformers import BertTokenizer, BertModel
from sklearn.svm import SVC
import torch
import numpy as np
import gradio as gr
import os
import joblib
from tqdm import tqdm

# Загрузка токенизатора и модели BERT
tokenizer = BertTokenizer.from_pretrained('bert-base-multilingual-cased')
bert_model = BertModel.from_pretrained('bert-base-multilingual-cased')

train_embeddings_bert = torch.load('train_bert.pt', map_location=torch.device('cpu'))
train_data = torch.load('train_data.pt', map_location=torch.device('cpu'))

# Пути к файлу модели и файлу с данными
model_path = 'svm_model.joblib'

# Функция для обучения модели и её сохранения
def train_and_save_model():
    model = SVC(kernel='linear', random_state=42)
    model.fit(train_embeddings_bert.cpu(), train_data['label'])
    joblib.dump(model, model_path)
    print("Модель обучена и сохранена в файл.")

# Проверка наличия файла модели
if not os.path.exists(model_path):
    print("Файл модели не найден, обучение модели...")
    train_and_save_model()
else:
    print("Файл модели найден, загрузка модели...")
    model = joblib.load(model_path)
    print("Модель загружена из файла.")

# Функция для преобразования текста в векторы с использованием BERT
def texts_to_vectors(texts, tokenizer, vec_model, vec_dim=768, bs=1, device='cpu'):
    Vectors = torch.zeros((len(texts), vec_dim)).to(device)
    for i in tqdm(range(0, len(texts), bs)):
        ind_from = i  # индекс начала порции данных (части массива)
        ind_to = i + bs  # индекс конца порции данных (части массива)
        text = texts[ind_from:ind_to]
        tokenized_text = tokenizer(text, padding=True, truncation=True, max_length=512, return_tensors='pt')
        with torch.no_grad():
            model_out = vec_model(**tokenized_text.to(device))
        Vectors[ind_from:ind_to] = model_out.pooler_output
    return Vectors

# Функция для предсказания токсичности текста
def predict_toxicity(text):
    # Предобработка входного текста
    text_vectorized = texts_to_vectors([text], tokenizer, bert_model, device='cpu')
    # Предсказание
    prediction = model.predict(text_vectorized.numpy())[0]
    return "Токсичный" if prediction == 1 else "Не токсичный"

# Интерфейс Gradio
iface = gr.Interface(
    fn=predict_toxicity,
    inputs=gr.Textbox(label="Введите ваше сообщение здесь..."),
    outputs=gr.Textbox(label="Результат"),
    title="Определение токсичности текста",
    description="Модель, определяющая является ли текст токсичным или нет."
)

# Запуск интерфейса Gradio
iface.launch()
